#include <stdint.h>

typedef struct {
    volatile uint32_t MODER;    // GPIO port mode register          Offset: 0x00
    volatile uint32_t OTYPER;   // GPIO port output type register   Offset: 0x04
    volatile uint32_t OSPEEDR;  // GPIO port output speed register  Offset: 0x08
    volatile uint32_t PUPDR;    // GPIO port pull-up/pull-down register Offset: 0x0C
    volatile uint32_t IDR;      // GPIO port input data register    Offset: 0x10
    volatile uint32_t ODR;      // GPIO port output data register   Offset: 0x14
    volatile uint32_t BSRR;     // GPIO port bit set/reset register Offset: 0x18
    volatile uint32_t LCKR;     // GPIO port configuration lock register Offset: 0x1C
    volatile uint32_t AFR[2];   // GPIO alternate function registers Offset: 0x20-0x24
} GPIO_TypeDef;

#define GPIOC_BASE 0x40020800
#define GPIOC ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOA_BASE 0x40020000
#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)
#define RCC_AHB1ENR (*(volatile uint32_t *)(0x40023830))

#define LEDPin 13      // Pin PC13 for LED (Blackpill uses PC13 for LED)
#define ButtonPin 0    // Pin PA0 for Button (or use another pin if you prefer)

int main(void)
{
    // Enable GPIOC clock (for LED on PC13)
    RCC_AHB1ENR |= (1 << 2);
    // Enable GPIOA clock (for Button on PA0)
    RCC_AHB1ENR |= (1 << 0);

    // Configure PC13 (LEDPin) as output
    GPIOC->MODER &= ~(0x3 << (LEDPin * 2));  // Clear mode bits for PC13
    GPIOC->MODER |= (0x1 << (LEDPin * 2));   // Set PC13 to output mode (01)
    GPIOC->OTYPER &= ~(1 << LEDPin);         // Set PC13 to push-pull (default)

    // Configure PA0 (ButtonPin) as input with pull-up resistor
    GPIOA->MODER &= ~(0x3 << (ButtonPin * 2));  // Set PA0 to input mode (00)
    GPIOA->PUPDR &= ~(0x3 << (ButtonPin * 2));  // Clear pull-up/pull-down bits
    GPIOA->PUPDR |= (0x1 << (ButtonPin * 2));   // Set PA0 to pull-up (01)

    uint8_t previousButtonState = 0;

    /* Main loop */
    while (1) {
        uint8_t currentButtonState = (GPIOA->IDR & (1 << ButtonPin));  // Read the button state
        if (currentButtonState && !previousButtonState) {              // Button pressed
            GPIOC->ODR ^= (1 << LEDPin); // Toggle LED on PC13
        }

        previousButtonState = currentButtonState;
        for (volatile int i = 0; i < 100000; i++);  // Delay
    }
}
