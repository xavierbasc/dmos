#define RCC_BASE 0x40023800
#define GPIOC_BASE 0x40020800

#define RCC_AHB1ENR (*(volatile unsigned int *)(RCC_BASE + 0x30))
#define GPIOC_MODER (*(volatile unsigned int *)(GPIOC_BASE + 0x00))
#define GPIOC_ODR (*(volatile unsigned int *)(GPIOC_BASE + 0x14))

void delay(volatile unsigned int count) {
    while (count--) {
        __asm__("nop");
    }
}

int main(void) {
    // Habilitar el reloj del GPIOC
    RCC_AHB1ENR |= (1 << 2);

    // Configurar PC13 como salida
    GPIOC_MODER &= ~(3 << (13 * 2)); // Limpiar bits
    GPIOC_MODER |= (1 << (13 * 2));  // Configurar como salida

    while (1) {
        // Encender LED (en PC13 el LED se apaga con 1)
        GPIOC_ODR &= ~(1 << 13);
        delay(1000000);

        // Apagar LED (en PC13 el LED se enciende con 0)
        GPIOC_ODR |= (1 << 13);
        delay(1000000);
    }

    return 0;
}
