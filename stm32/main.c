#include <stdint.h>

// GPIO
#define RCC_AHB1ENR (*((volatile uint32_t *)0x40023830)) // Register to enable GPIO clock
#define GPIOA_MODER (*((volatile uint32_t *)0x40020000)) // Register for GPIOA mode
#define GPIOA_ODR   (*((volatile uint32_t *)0x40020014)) // Register for GPIOA output

#define PIN_RS      (1 << 0)  // Pin for RS (A0)
#define PIN_CS      (1 << 1)  // Pin for CS
#define PIN_RESET   (1 << 2)  // Pin for RSE

void GPIO_Init(void) {
    RCC_AHB1ENR |= (1 << 0);   // Enable GPIOA clock

    // Configure pins as output (general purpose output mode, bits 01 in the MODER register)
    GPIOA_MODER |= (1 << (0 * 2));  // PA0 -> RS
    GPIOA_MODER |= (1 << (1 * 2));  // PA1 -> CS
    GPIOA_MODER |= (1 << (2 * 2));  // PA2 -> RESET
}

// SPI
#define RCC_APB2ENR (*((volatile uint32_t *)0x40023844)) // Register to enable SPI1 clock on APB2
#define SPI1_CR1    (*((volatile uint32_t *)0x40013000)) // SPI1 control register
#define SPI1_SR     (*((volatile uint32_t *)0x40013008)) // SPI1 status register
#define SPI1_DR     (*((volatile uint32_t *)0x4001300C)) // SPI1 data register

void SPI_Init(void) {
    RCC_APB2ENR |= (1 << 12);  // Enable SPI1 clock

    // Configure SPI: Master, mode 0, 8 bits per word, enable SPI
    SPI1_CR1 = (1 << 2) | (1 << 8) | (1 << 6); // BR[2:0]=0b000, MSTR=1, SPE=1
}

void SPI_Write(uint8_t data) {
    while (!(SPI1_SR & (1 << 1))); // Wait until TXE (transmit buffer empty)
    SPI1_DR = data;                // Send data
    while (SPI1_SR & (1 << 7));    // Wait until the transmission is complete
}

// DISPLAY
void SendCommand(uint8_t cmd) {
    GPIOA_ODR &= ~PIN_RS;   // RS low (command mode)
    GPIOA_ODR &= ~PIN_CS;   // CS low (activate chip)
    SPI_Write(cmd);
    GPIOA_ODR |= PIN_CS;    // CS high (deactivate chip)
}

void SendData(uint8_t data) {
    GPIOA_ODR |= PIN_RS;    // RS high (data mode)
    GPIOA_ODR &= ~PIN_CS;   // CS low (activate chip)
    SPI_Write(data);
    GPIOA_ODR |= PIN_CS;    // CS high (deactivate chip)
}

void Display_Init(void) {
    SendCommand(0xAE); // Display OFF
    SendCommand(0xA2); // Bias 1/9
    SendCommand(0xA0); // SEG normal
    SendCommand(0xC8); // COM remap
    SendCommand(0xA4); // Normal display
    SendCommand(0x40); // Set start line
    SendCommand(0xAF); // Display ON
}

void DrawPoint(uint8_t x, uint8_t y) {
    SendCommand(0xB0 + (y / 8)); // Set page address
    SendCommand(x & 0x0F);       // Set lower column address
    SendCommand(0x10 | (x >> 4)); // Set higher column address
    SendData(1 << (y % 8));      // Set pixel
}


// MAIN
int main(void) {
    GPIO_Init();
    SPI_Init();
    Display_Init();

    DrawPoint(10, 10); // Draw a point at (10, 10)

    while (1);
}
