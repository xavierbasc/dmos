#include <stdint.h>
#include "stm32f4xx.h"

#define ISR_VECTOR_SIZE_WORDS 102 // Total exception count + interrupt count + 2

// Provided by linker
extern uint32_t _estack, _sdata, _edata, _sbss, _ebss, _sidata;

int main (void);
void __libc_init_array();


// Cortex-M4 system exceptions
void Default_Handler                    (void);
void Reset_Handler                      (void);

void NMI_Handler                        (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler                  (void) __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler                  (void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler                   (void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler                        (void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler                   (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler                     (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler                    (void) __attribute__ ((weak, alias("Default_Handler")));


// STM32F411xC/E interrupt handlers
void WWDG_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
void PVD_IRQHandler                     (void) __attribute__ ((weak, alias("Default_Handler")));
void TAMP_STAMP_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_WKUP_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void FLASH_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
void RCC_IRQHandler                     (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI0_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI1_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI2_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI3_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI4_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream0_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream1_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream2_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream3_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream4_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream5_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream6_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC_IRQHandler                     (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI9_5_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_BRK_TIM9_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_UP_TIM10_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM11_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM2_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM3_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM4_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_EV_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_ER_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI2_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
void USART1_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
void USART2_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI15_10_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_Alarm_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_WKUP_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream7_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void SDIO_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM5_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI3_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream0_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream1_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream2_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream3_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream4_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream5_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream6_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream7_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void USART6_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_EV_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_ER_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_IRQHandler                     (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI4_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI5_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));


uint32_t isr_vector[ISR_VECTOR_SIZE_WORDS] __attribute__ ((section(".isr_vector"))) = {
    (uint32_t)&_estack,                         // 0x0000 0000          Initial Stack Pointer
    // Cortex-M4 system exceptions
    (uint32_t)&Reset_Handler,                   // 0x0000 0004          Reset
    (uint32_t)&NMI_Handler,                     // 0x0000 0008          Non Maskable Interrupt
    (uint32_t)&HardFault_Handler,               // 0x0000 000C          All class of fault
    (uint32_t)&MemManage_Handler,               // 0x0000 0010          Memory management
    (uint32_t)&BusFault_Handler,                // 0x0000 0014          Pre-fetch fault / Memory access fault
    (uint32_t)&UsageFault_Handler,              // 0x0000 0018          Undefined instruction or illegal state
    0,                                          // 0x0000 001C          Reserved
    0,                                          // 0x0000 0020          Reserved
    0,                                          // 0x0000 0024          Reserved
    0,                                          // 0x0000 0028          Reserved
    (uint32_t)&SVC_Handler,                     // 0x0000 002C          System Service call via SWI instruction
    (uint32_t)&DebugMon_Handler,                // 0x0000 0030          Debug Monitor
    0,                                          // 0x0000 0034          Reserved
    (uint32_t)&PendSV_Handler,                  // 0x0000 0038          Pendable request for system service
    (uint32_t)&SysTick_Handler,                 // 0x0000 003C          System tick timer
    /* STM32F411xC/E interrupt handlers, see chapter 10.1.3 Interrupt and exception vector table 37 of Reference manual */
    (uint32_t)&WWDG_IRQHandler,                 // 0x0000 0040          Window WatchDog
    (uint32_t)&PVD_IRQHandler,                  // 0x0000 0044          EXTI Line 16 / PVD through EXTI line detection
    (uint32_t)&TAMP_STAMP_IRQHandler,           // 0x0000 0048          EXTI Line 21 / Tamper and TimeStamp through EXTI line
    (uint32_t)&RTC_WKUP_IRQHandler,             // 0x0000 004C          EXTI Line 22 / RTC Wakeup through EXTI line
    (uint32_t)&FLASH_IRQHandler,                // 0x0000 0050          Flash global
    (uint32_t)&RCC_IRQHandler,                  // 0x0000 0054          RCC global
    (uint32_t)&EXTI0_IRQHandler,                // 0x0000 0058          EXTI Line0
    (uint32_t)&EXTI1_IRQHandler,                // 0x0000 005C          EXTI Line1
    (uint32_t)&EXTI2_IRQHandler,                // 0x0000 0060          EXTI Line2
    (uint32_t)&EXTI3_IRQHandler,                // 0x0000 0064          EXTI Line3
    (uint32_t)&EXTI4_IRQHandler,                // 0x0000 0068          EXTI Line4
    (uint32_t)&DMA1_Stream0_IRQHandler,         // 0x0000 006C          DMA1 Stream0 global
    (uint32_t)&DMA1_Stream1_IRQHandler,         // 0x0000 0070          DMA1 Stream1 global
    (uint32_t)&DMA1_Stream2_IRQHandler,         // 0x0000 0074          DMA1 Stream2 global
    (uint32_t)&DMA1_Stream3_IRQHandler,         // 0x0000 0078          DMA1 Stream3 global
    (uint32_t)&DMA1_Stream4_IRQHandler,         // 0x0000 007C          DMA1 Stream4 global
    (uint32_t)&DMA1_Stream5_IRQHandler,         // 0x0000 0080          DMA1 Stream5 global
    (uint32_t)&DMA1_Stream6_IRQHandler,         // 0x0000 0084          DMA1 Stream6 global
    (uint32_t)&ADC_IRQHandler,                  // 0x0000 0088          ADC1 global
    0,                                          // 0x0000 008C          Reserved
    0,                                          // 0x0000 0090          Reserved
    0,                                          // 0x0000 0094          Reserved
    0,                                          // 0x0000 0098          Reserved
    (uint32_t)&EXTI9_5_IRQHandler,              // 0x0000 009C          EXTI Line[9:5]s
    (uint32_t)&TIM1_BRK_TIM9_IRQHandler,        // 0x0000 00A0          TIM1 Break / TIM9 global
    (uint32_t)&TIM1_UP_TIM10_IRQHandler,        // 0x0000 00A4          TIM1 Update / TIM10 global
    (uint32_t)&TIM1_TRG_COM_TIM11_IRQHandler,   // 0x0000 00A8          TIM1 Trigger / Commutation / TIM11 global
    (uint32_t)&TIM1_CC_IRQHandler,              // 0x0000 00AC          TIM1 Capture Compare
    (uint32_t)&TIM2_IRQHandler,                 // 0x0000 00B0          TIM2 global
    (uint32_t)&TIM3_IRQHandler,                 // 0x0000 00B4          TIM3 global
    (uint32_t)&TIM4_IRQHandler,                 // 0x0000 00B8          TIM4 global
    (uint32_t)&I2C1_EV_IRQHandler,              // 0x0000 00BC          I2C1 Event
    (uint32_t)&I2C1_ER_IRQHandler,              // 0x0000 00C0          I2C1 Error
    (uint32_t)&I2C2_EV_IRQHandler,              // 0x0000 00C4          I2C2 Event
    (uint32_t)&I2C2_ER_IRQHandler,              // 0x0000 00C8          I2C2 Error
    (uint32_t)&SPI1_IRQHandler,                 // 0x0000 00CC          SPI1 global
    (uint32_t)&SPI2_IRQHandler,                 // 0x0000 00D0          SPI2 global
    (uint32_t)&USART1_IRQHandler,               // 0x0000 00D4          USART1 global
    (uint32_t)&USART2_IRQHandler,               // 0x0000 00D8          USART2 global
    0,                                          // 0x0000 00DC          Reserved
    (uint32_t)&EXTI15_10_IRQHandler,            // 0x0000 00E0          EXTI Line[15:10]s
    (uint32_t)&RTC_Alarm_IRQHandler,            // 0x0000 00E4          EXTI Line 17 / RTC Alarm (A and B) through EXTI line
    (uint32_t)&OTG_FS_WKUP_IRQHandler,          // 0x0000 00E8          EXTI Line 18 / USB On-The-Go FS Wakeup through EXTI line
    0,                                          // 0x0000 00EC          Reserved
    0,                                          // 0x0000 00F0          Reserved
    0,                                          // 0x0000 00F4          Reserved
    0,                                          // 0x0000 00F8          Reserved
    (uint32_t)&DMA1_Stream7_IRQHandler,         // 0x0000 00FC          DMA1 Stream7 global
    0,                                          // 0x0000 0100          Reserved
    (uint32_t)&SDIO_IRQHandler,                 // 0x0000 0104          SDIO global
    (uint32_t)&TIM5_IRQHandler,                 // 0x0000 0108          TIM5 global
    (uint32_t)&SPI3_IRQHandler,                 // 0x0000 010C          SPI3 global
    0,                                          // 0x0000 0110          Reserved
    0,                                          // 0x0000 0114          Reserved
    0,                                          // 0x0000 0118          Reserved
    0,                                          // 0x0000 011C          Reserved
    (uint32_t)&DMA2_Stream0_IRQHandler,         // 0x0000 0120          DMA2 Stream0 global
    (uint32_t)&DMA2_Stream1_IRQHandler,         // 0x0000 0124          DMA2 Stream1 global
    (uint32_t)&DMA2_Stream2_IRQHandler,         // 0x0000 0128          DMA2 Stream2 global
    (uint32_t)&DMA2_Stream3_IRQHandler,         // 0x0000 012C          DMA2 Stream3 global
    (uint32_t)&DMA2_Stream4_IRQHandler,         // 0x0000 0130          DMA2 Stream4 global
    0,                                          // 0x0000 0134          Reserved
    0,                                          // 0x0000 0138          Reserved
    0,                                          // 0x0000 013C          Reserved
    0,                                          // 0x0000 0140          Reserved
    0,                                          // 0x0000 0144          Reserved
    0,                                          // 0x0000 0148          Reserved
    (uint32_t)&OTG_FS_IRQHandler,               // 0x0000 014C          USB On-The-Go FS global
    (uint32_t)&DMA2_Stream5_IRQHandler,         // 0x0000 0150          DMA2 Stream5 global
    (uint32_t)&DMA2_Stream6_IRQHandler,         // 0x0000 0154          DMA2 Stream6 global
    (uint32_t)&DMA2_Stream7_IRQHandler,         // 0x0000 0158          DMA2 Stream7 global
    (uint32_t)&USART6_IRQHandler,               // 0x0000 015C          USART6 global
    (uint32_t)&I2C3_EV_IRQHandler,              // 0x0000 0160          I2C3 Event
    (uint32_t)&I2C3_ER_IRQHandler,              // 0x0000 0164          I2C3 Error
    0,                                          // 0x0000 0168          Reserved
    0,                                          // 0x0000 016C          Reserved
    0,                                          // 0x0000 0170          Reserved
    0,                                          // 0x0000 0174          Reserved
    0,                                          // 0x0000 0178          Reserved
    0,                                          // 0x0000 017C          Reserved
    0,                                          // 0x0000 0180          Reserved
    (uint32_t)&FPU_IRQHandler,                  // 0x0000 0184          FPU global
    0,                                          // 0x0000 0188          Reserved
    0,                                          // 0x0000 018C          Reserved
    (uint32_t)&SPI4_IRQHandler,                 // 0x0000 0190          SPI4 global
    (uint32_t)&SPI5_IRQHandler                  // 0x0000 0194          SPI5 global
};


void Reset_Handler (void)
{
    // Copy .data from FLASH to RAM
    uint32_t data_size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t *flash_data = (uint8_t*) &_sidata; // Data load address (in FLASH)
    uint8_t *sram_data = (uint8_t*) &_sdata; // Data virtual address (in RAM)

    for (uint32_t i = 0; i < data_size; i++)
    {
        sram_data[i] = flash_data[i];
    }

    // Zero-fill .bss section in RAM
    uint32_t bss_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    uint8_t *bss = (uint8_t*) &_sbss;

    for (uint32_t i = 0; i < bss_size; i++)
    {
        bss[i] = 0;
    }

    // Configure FPU, external SRAM and vector table relocation if defined
    SystemInit();

    main();
}


void Default_Handler (void)
{
    while(1);
}
