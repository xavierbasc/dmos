#include <stdint.h>
#include "stm32f4xx.h"

#define LED_PIN 13

int main (void)
{
    // Enable clock at GPIO port C
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN_Msk;
    // Execute dsb instruction after enabling the peripheral clock, as per the errata
    __DSB();

    // Set pin 13 connected to blue led of port C as output
    GPIOC->MODER |= (1 << GPIO_MODER_MODER13_Pos);

    while(1)
    {
        GPIOC->ODR ^= (1 << LED_PIN);
        for (uint32_t i = 0; i < 1000000; i++);
    }

    return(0);
}
