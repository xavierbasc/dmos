#include "stm32f4xx.h"

/*
Display Pin	Descripción   STM32F411 Pin Función
----------- ------------- ------------- ---------
RS	        Comando/Dato  PA3           GPIO: Selecciona comando o dato.
RSE         Reset         PA4           GPIO: Resetea el display.
SCL         Reloj SPI     PA5           SPI1_SCK: Clock de SPI.
CS          Chip Select   PA6           GPIO: Selecciona el display.
SI          Datos SPI     PA7           SPI1_MOSI: Datos de SPI.
*/

void GPIO_Init(void) {
    // Habilitar el reloj para GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Configurar PA3 (RS), PA4 (RSE), PA6 (CS) como salidas
    GPIOA->MODER &= ~((3 << GPIO_MODER_MODER3_Pos) |
                      (3 << GPIO_MODER_MODER4_Pos) |
                      (3 << GPIO_MODER_MODER6_Pos)); // Limpiar bits
    GPIOA->MODER |= (1 << GPIO_MODER_MODER3_Pos) | // Modo salida
                    (1 << GPIO_MODER_MODER4_Pos) |
                    (1 << GPIO_MODER_MODER6_Pos);

    // Configurar PA5 (SCL) y PA7 (SI) como alternativos para SPI1
    GPIOA->MODER &= ~((3 << GPIO_MODER_MODER5_Pos) |
                      (3 << GPIO_MODER_MODER7_Pos)); // Limpiar bits
    GPIOA->MODER |= (2 << GPIO_MODER_MODER5_Pos) | // Modo alternativo
                    (2 << GPIO_MODER_MODER7_Pos);

    GPIOA->AFR[0] &= ~((0xF << GPIO_AFRL_AFSEL5_Pos) | 
                       (0xF << GPIO_AFRL_AFSEL7_Pos)); // Limpiar AF
    GPIOA->AFR[0] |= (5 << GPIO_AFRL_AFSEL5_Pos) | // AF5 (SPI1)
                     (5 << GPIO_AFRL_AFSEL7_Pos);


    // Habilitar el reloj para GPIOC
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    // Configurar PC13 como salida (modo push-pull)
    GPIOC->MODER &= ~GPIO_MODER_MODE13;     // Limpiar bits de modo
    GPIOC->MODER |= GPIO_MODER_MODE13_0;    // Configurar como salida (modo general)

    GPIOC->OTYPER &= ~GPIO_OTYPER_OT_13;    // Configurar como salida push-pull
    GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED13; // Velocidad alta para la salida
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR13;    // Sin resistencias pull-up o pull-down

}


void SPI1_Init(void) {
    // Habilitar el reloj para SPI1
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    // Configurar SPI1: Modo maestro, CPOL=0, CPHA=0, prescaler=16
    SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_BR_1 | SPI_CR1_BR_0; // Modo maestro, prescaler 16
    SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI; // NSS en software
    SPI1->CR1 |= SPI_CR1_SPE; // Habilitar SPI1
}

void SPI1_Send(uint8_t data) {
    while (!(SPI1->SR & SPI_SR_TXE)); // Esperar que TX esté listo
    SPI1->DR = data; // Enviar dato
    while (!(SPI1->SR & SPI_SR_RXNE)); // Esperar recepción
    (void)SPI1->DR; // Leer el dato recibido (descartar)
}

void ST7565_Reset(void) {
    GPIOA->BSRR = GPIO_BSRR_BR4; // RSE bajo
    for (volatile int i = 0; i < 10000; i++); // Pequeño retardo
    GPIOA->BSRR = GPIO_BSRR_BS4; // RSE alto
}

void ST7565_Command(uint8_t cmd) {
    GPIOA->BSRR = GPIO_BSRR_BR3; // RS bajo (comando)
    GPIOA->BSRR = GPIO_BSRR_BR6; // CS bajo
    SPI1_Send(cmd);
    GPIOA->BSRR = GPIO_BSRR_BS6; // CS alto
}

void ST7565_Data(uint8_t data) {
    GPIOA->BSRR = GPIO_BSRR_BS3; // RS alto (datos)
    GPIOA->BSRR = GPIO_BSRR_BR6; // CS bajo
    SPI1_Send(data);
    GPIOA->BSRR = GPIO_BSRR_BS6; // CS alto
}

void ST7565_Init(void) {
    ST7565_Reset();
    ST7565_Command(0xAE); // Apagar el display
    ST7565_Command(0xA2); // Bias 1/9
    ST7565_Command(0xA1); // Segmento invertido
    ST7565_Command(0xC0); // Dirección de escaneo normal
    ST7565_Command(0xA6); // Modo normal

    // Comando para configurar el contraste
    ST7565_Command(0x81); // Comando de ajuste de contraste
    ST7565_Command(0x3F); // Establecer el contraste al máximo (0x3F)
    
    ST7565_Command(0xAF); // Encender el display
    for (volatile int i = 0; i < 10000; i++); // Retardo extra
}

void ST7565_DrawPixel(uint8_t x, uint8_t y) {
    uint8_t page = y / 8; // Página (línea)
    uint8_t bit = 1 << (y % 8); // Bit dentro de la página

    ST7565_Command(0xB0 | page); // Seleccionar página
    ST7565_Command(0x10 | (x >> 4)); // Columna alta
    ST7565_Command(0x00 | (x & 0x0F)); // Columna baja

    ST7565_Data(bit); // Encender el bit correspondiente
}

// Función para hacer parpadear el LED
void delay(volatile int count) {
    while(count--) {
        // Loop vacío para generar un retardo
    }
}


int main(void) {
    GPIO_Init();
    SPI1_Init();
    ST7565_Init();
    while (1) {
        ST7565_DrawPixel(10, 10); // Dibuja un punto en (10, 10)
        // Encender el LED (PC13)
        GPIOC->BSRR = GPIO_BSRR_BS13;  // Establecer el bit de salida (LED ON)
        delay(1000000);  // Retardo (ajusta para cambiar la velocidad de parpadeo)
        // Apagar el LED (PC13)
        GPIOC->BSRR = GPIO_BSRR_BR13;  // Borrar el bit de salida (LED OFF)
        delay(1000000);  // Retardo
        //for (volatile int i = 0; i < 100000; i++); // Retardo para ver el punto
    }
}
