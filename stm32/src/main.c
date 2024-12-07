#include "stm32f4xx.h"

#define LCDWIDTH 132
#define LCDHEIGHT 128
uint8_t buffer[LCDWIDTH * LCDHEIGHT / 8] = {0}; // Buffer para la pantalla

/*
Display Pin	Descripción   STM32F411 Pin Función
----------- ------------- ------------- ---------
RS	        Comando/Dato  PA3           GPIO: Selecciona comando o dato.
RSE         Reset         PA4           GPIO: Resetea el display.
SCL         Reloj SPI     PA5           SPI1_SCK: Clock de SPI.
CS          Chip Select   PA6           GPIO: Selecciona el display.
SI          Datos SPI     PA7           SPI1_MOSI: Datos de SPI.
*/

/******************************delay time***********************************/  
void delay_ms(unsigned int ms)  
{  
 unsigned int n ;  
 while(ms--)  
      {  
       n  =  8600 * 4;  
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
    delay_ms(50);  
    GPIOA->BSRR = GPIO_BSRR_BS4; // RSE alto
    delay_ms(50);  
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
    ST7565_Reset(); // Resetear el display
    ST7565_Command(0xAE); // Apagar el display

    ST7565_Command(0xA3); //LCD Bias selection(1/65 Duty,1/7Bias)   

    ST7565_Command(0xA0); //ADC selection(SEG0->SEG128)  
    // ROTACION
    //ST7565_Command(0xC8); // C0: Dirección de escaneo normal (de arriba hacia abajo) C8: Dirección de escaneo invertida (de abajo hacia arriba)
    //ST7565_Command(0xA0); // A0: Normal (izquierda a derecha) 0xA1: Invertido (de derecha a izquierda)

    //ST7565_Command(0xA6); // A6: Modo normal (cambia a 0xA7 para modo inverso)

    ST7565_Command(0x26); //Regulator Resistor Selection   
    ST7565_Command(0x81); //Electronic Volume   
    ST7565_Command(0x20); //Reference Register selection  Vo=(1+Rb/Ra)(1+a)*2.1=10   

    ST7565_Command(0x2F); // Enciende todos los bloques internos (encender el bias y la oscilación)
    delay_ms(10);

    // Ajuste del contraste (puedes probar con otros valores si es necesario)
    ST7565_Command(0x81); // Comando de ajuste de contraste
    ST7565_Command(0x06); // Contraste (puedes ajustar según necesites) 0x00 - 0x3F
    
    ST7565_Command(0xAF); // Encender el display

    // Pausar brevemente para asegurar que el display esté listo
    for (volatile int i = 0; i < 10000; i++);
}

// Función para leer datos de la memoria del display (debe implementarse según las especificaciones del hardware)
uint8_t ST7565_ReadData(void) {
    uint8_t receivedData = 0;
    
    // Comando de lectura (esto depende de cómo esté configurado el hardware para leer datos)
    // Debes implementar la lectura de datos SPI, similar a cómo envías comandos o datos.

    // Por ejemplo, podrías poner CS bajo, RS alto para leer datos:
    GPIOA->BSRR = GPIO_BSRR_BR6;        // CS bajo
    GPIOA->BSRR = GPIO_BSRR_BS3;        // RS alto (modo de datos)
    
    // Esperar hasta que SPI esté listo para recibir
    while (!(SPI1->SR & SPI_SR_TXE));   // Esperar a que el registro de transmisión esté vacío
    SPI1->DR = 0x00;                     // Enviar un valor nulo para obtener datos
    while (!(SPI1->SR & SPI_SR_RXNE));  // Esperar a que haya datos disponibles
    receivedData = SPI1->DR;            // Leer el dato recibido

    GPIOA->BSRR = GPIO_BSRR_BS6;        // CS alto

    return receivedData;                 // Devolver el dato leído
}

// Define la función setpixel para actualizar un píxel específico
void setpixel(uint8_t *buff, uint8_t x, uint8_t y, uint8_t color) {
    if ((x >= LCDWIDTH) || (y >= LCDHEIGHT))
        return;

    // x es la columna y y es la fila. Ajuste para páginas de 8 píxeles de altura.
    if (color)
        buff[x + (y / 8) * LCDWIDTH] |= (1 << (7 - (y % 8)));  // Set the pixel
    else
        buff[x + (y / 8) * LCDWIDTH] &= ~(1 << (7 - (y % 8))); // Clear the pixel
}

// Función para dibujar un punto específico en el buffer
void ST7565_DrawPixel(uint8_t x, uint8_t y, uint8_t color) {
    setpixel(buffer, x, y, color);  // Llama a setpixel para dibujar el píxel en el búfer
}

// Función para actualizar la pantalla con el contenido del buffer
void ST7565_UpdateDisplay(void) {
    for (uint8_t page = 0; page < 8; page++) { // Iterar sobre las 8 páginas (64 píxeles de altura)
        ST7565_Command(0xB0 | page);  // Seleccionar página
        ST7565_Command(0x10);         // Columna alta
        ST7565_Command(0x00);         // Columna baja
        
        for (uint8_t x = 0; x < LCDWIDTH; x++) { // Iterar sobre todas las columnas (128 píxeles de ancho)
            ST7565_Data(buffer[x + page * LCDWIDTH]); // Enviar los datos del búfer a la pantalla
        }
    }
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

    // Limpiar el buffer al inicio
    memset(buffer, 0, sizeof(buffer));

    while (1) {
        
        // Encender el LED (PC13)
        GPIOC->BSRR = GPIO_BSRR_BS13;  // Establecer el bit de salida (LED ON)
        delay(1000000);  // Retardo (ajusta para cambiar la velocidad de parpadeo)

        // Dibujar los puntos deseados en las coordenadas
        ST7565_DrawPixel(0, 0, 1);
        ST7565_DrawPixel(0, 63, 1);
        ST7565_DrawPixel(127, 0, 1);
        ST7565_DrawPixel(127, 63, 1);
        ST7565_DrawPixel(127, 64, 1);

        ST7565_DrawPixel(0, 0, 1);

        ST7565_UpdateDisplay();

        // Apagar el LED (PC13)
        GPIOC->BSRR = GPIO_BSRR_BR13;  // Borrar el bit de salida (LED OFF)
        delay(1000000);  // Retardo
    }
}
