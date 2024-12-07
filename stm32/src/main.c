#include <string.h>
#include <stdlib.h>
#include "stm32f4xx.h"

#define LCDWIDTH 132 // 128 pixels, 132 buffer
#define LCDHEIGHT 64
uint8_t buffer[LCDWIDTH * LCDHEIGHT / 8] = {0}; // Buffer for the display

/*
Display Pin	Description   STM32F411 Pin  Function
----------- ------------- -------------  ---------
RS	        Command/Data  PA3           GPIO: Selects command or data.
RSE         Reset         PA4           GPIO: Resets the display.
SCL         SPI Clock     PA5           SPI1_SCK: SPI Clock.
CS          Chip Select   PA6           GPIO: Selects the display.
SI          SPI Data      PA7           SPI1_MOSI: SPI Data.
*/

/******************************delay time***********************************/  
void delay_ms(unsigned int ms)  
{  
    unsigned int n;  
    while(ms--)  
    {  
        n = 8600 * 4;  
        while(n--)
        {
            asm("nop");
        }
    }  
} 

static inline void NOP(void)
{
    int i = 2;
    while(i--)
        asm("nop");
}

// GPIO initialization
void GPIO_Init(void) {
    // Enable clock for GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Configure PA3 (RS), PA4 (RSE), PA6 (CS) as outputs
    GPIOA->MODER &= ~((3 << GPIO_MODER_MODER3_Pos) |
                      (3 << GPIO_MODER_MODER4_Pos) |
                      (3 << GPIO_MODER_MODER6_Pos)); // Clear bits
    GPIOA->MODER |= (1 << GPIO_MODER_MODER3_Pos) | // Output mode
                    (1 << GPIO_MODER_MODER4_Pos) |
                    (1 << GPIO_MODER_MODER6_Pos);

    // Configure PA5 (SCL) and PA7 (SI) as alternate for SPI1
    GPIOA->MODER &= ~((3 << GPIO_MODER_MODER5_Pos) |
                      (3 << GPIO_MODER_MODER7_Pos)); // Clear bits
    GPIOA->MODER |= (2 << GPIO_MODER_MODER5_Pos) | // Alternate mode
                    (2 << GPIO_MODER_MODER7_Pos);

    GPIOA->AFR[0] &= ~((0xF << GPIO_AFRL_AFSEL5_Pos) | 
                       (0xF << GPIO_AFRL_AFSEL7_Pos)); // Clear AF
    GPIOA->AFR[0] |= (5 << GPIO_AFRL_AFSEL5_Pos) | // AF5 (SPI1)
                     (5 << GPIO_AFRL_AFSEL7_Pos);

    // Enable clock for GPIOC
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    // Configure PC13 as output (push-pull mode)
    GPIOC->MODER &= ~GPIO_MODER_MODE13;     // Clear mode bits
    GPIOC->MODER |= GPIO_MODER_MODE13_0;    // Configure as output (general mode)

    GPIOC->OTYPER &= ~GPIO_OTYPER_OT_13;    // Configure as push-pull output
    GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED13; // High-speed output
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR13;    // No pull-up or pull-down
}

// SPI1 initialization
void SPI1_Init(void) {
    // Enable clock for SPI1
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    // Configure SPI1: Master mode, CPOL=0, CPHA=0, prescaler=16
    SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_BR_1 | SPI_CR1_BR_0; // Master mode, prescaler 16
    SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI; // NSS in software
    SPI1->CR1 |= SPI_CR1_SPE; // Enable SPI1
}

// Send data via SPI1
void SPI1_Send(uint8_t data) {
    while (!(SPI1->SR & SPI_SR_TXE)); // Wait until TX is ready
    SPI1->DR = data; // Send data
    while (!(SPI1->SR & SPI_SR_RXNE)); // Wait for reception
    (void)SPI1->DR; // Read received data (discard it)
}

// Reset the ST7565 display
void ST7565_Reset(void) {
    GPIOA->BSRR = GPIO_BSRR_BR4; // RSE low
    delay_ms(50);  
    GPIOA->BSRR = GPIO_BSRR_BS4; // RSE high
    delay_ms(50);  
}

// Send a command to the ST7565 display
void ST7565_Command(uint8_t cmd) {
    GPIOA->BSRR = GPIO_BSRR_BR3; // RS low (command)
    GPIOA->BSRR = GPIO_BSRR_BR6; // CS low
    SPI1_Send(cmd);
    GPIOA->BSRR = GPIO_BSRR_BS6; // CS high
}

// Send data to the ST7565 display
void ST7565_Data(uint8_t data) {
    GPIOA->BSRR = GPIO_BSRR_BS3; // RS high (data)
    GPIOA->BSRR = GPIO_BSRR_BR6; // CS low
    SPI1_Send(data);
    GPIOA->BSRR = GPIO_BSRR_BS6; // CS high
}

// Initialize the ST7565 display
void ST7565_Init(void) {
    ST7565_Reset(); // Reset the display
    ST7565_Command(0xAE); // Turn off the display

    ST7565_Command(0xA3); // LCD Bias selection (1/65 Duty, 1/7 Bias)   
    ST7565_Command(0xA0); // ADC selection (SEG0->SEG128)  

    // Rotation
    // ST7565_Command(0xC8); // C0: Normal scan direction (top to bottom), C8: Inverted scan (bottom to top)
    // ST7565_Command(0xA0); // A0: Normal (left to right), 0xA1: Inverted (right to left)
    // ST7565_Command(0xA6); // A6: Normal mode (switch to 0xA7 for inverted mode)

    ST7565_Command(0x26); // Regulator Resistor Selection   
    ST7565_Command(0x81); // Electronic Volume   
    ST7565_Command(0x20); // Reference Register selection Vo=(1+Rb/Ra)(1+a)*2.1=10   

    ST7565_Command(0x2F); // Turn on all internal blocks (enable bias and oscillation)
    delay_ms(10);

    // Contrast adjustment (try other values if needed)
    ST7565_Command(0x81); // Contrast adjustment command
    ST7565_Command(0x06); // Contrast value (adjust as needed) 0x00 - 0x3F
    
    ST7565_Command(0xAF); // Turn on the display

    // Pause briefly to ensure the display is ready
    for (volatile int i = 0; i < 10000; i++);
}

// Function to read data from the display memory (must be implemented according to hardware specifications)
uint8_t ST7565_ReadData(void) {
    uint8_t receivedData = 0;
    
    // Read command (this depends on how the hardware is configured to read data)
    // You need to implement SPI data reading, similar to how commands or data are sent.

    // For example, you might set CS low and RS high to read data:
    GPIOA->BSRR = GPIO_BSRR_BR6;        // CS low
    GPIOA->BSRR = GPIO_BSRR_BS3;        // RS high (data mode)
    
    // Wait until SPI is ready to receive
    while (!(SPI1->SR & SPI_SR_TXE));   // Wait for the transmit register to be empty
    SPI1->DR = 0x00;                    // Send a null value to receive data
    while (!(SPI1->SR & SPI_SR_RXNE));  // Wait until data is available
    receivedData = SPI1->DR;            // Read the received data

    GPIOA->BSRR = GPIO_BSRR_BS6;        // CS high

    return receivedData;                 // Return the received data
}

// Define the setpixel function to update a specific pixel
void setpixel(uint8_t *buff, uint8_t x, uint8_t y, uint8_t color) {
    if ((x >= LCDWIDTH) || (y >= LCDHEIGHT)) // Check display boundaries
        return;

    // Calculate the address in the buffer
    uint16_t index = x + (y / 8) * LCDWIDTH; // Buffer address

    // Determine the bit in the corresponding byte
    uint8_t bit = y % 8; // The bit corresponding to the row

    if (color) 
        buff[index] |= (1 << bit); // Set the bit
    else
        buff[index] &= ~(1 << bit); // Clear the bit
}

// Function to draw a specific point in the buffer
void ST7565_DrawPixel(uint8_t x, uint8_t y, uint8_t color) {
    setpixel(buffer, x, y, color);  // Call setpixel to draw the pixel in the buffer
}

void ST7565_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;

    while (1) {
        ST7565_DrawPixel(x0, y0, color); // Draw the current pixel

        // Check if we have reached the end
        if (x0 == x1 && y0 == y1)
            break;

        int e2 = err * 2;

        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

// Function to update the display with the buffer content
void ST7565_UpdateDisplay(void) {
    for (uint8_t page = 0; page < 8; page++) { // Iterate through the 8 pages (64 pixels in height)
        // Select the current page
        ST7565_Command(0xB0 | page);  // Select the page (0xB0 + page number)

        // Set the starting column (0)
        ST7565_Command(0x10); // High part of the column address (bits 8-4)
        ST7565_Command(0x00); // Low part of the column address (bits 3-0)

        // Send all data for the current page from the buffer
        for (uint8_t x = 0; x < LCDWIDTH; x++) { // Iterate through columns (128 pixels in width)
            ST7565_Data(buffer[x + page * LCDWIDTH]);
        }
    }
}

// Function to blink the LED
void delay(volatile int count) {
    while(count--) {
        // Empty loop to generate a delay
    }
}

int main(void) {
    GPIO_Init();
    SPI1_Init();
    ST7565_Init();

    // Clear the buffer at startup
    memset(buffer, 0, sizeof(buffer));

    ST7565_DrawLine(  0,  0, 127,  0, 1);
    ST7565_DrawLine(  0, 63, 127, 63, 1);
    ST7565_DrawLine(  0,  0,   0, 63, 1);
    ST7565_DrawLine(127,  0, 127, 63, 1);

    while (1) {
        
        // Turn on the LED (PC13)
        GPIOC->BSRR = GPIO_BSRR_BS13;  // Set the output bit (LED ON)
        delay(1000000);  // Delay (adjust to change blink speed)
        ST7565_UpdateDisplay();

        // Turn off the LED (PC13)
        GPIOC->BSRR = GPIO_BSRR_BR13;  // Clear the output bit (LED OFF)
        delay(1000000);  // Delay
    }
}
