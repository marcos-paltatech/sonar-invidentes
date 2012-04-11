#include "stm32f10x_it.h"
#include "global.h"
#include <stdio.h>

void setupITs()
{
    // Setear "Interrupt and exception vectors table"
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x00);
    // Configurar tabla de prioridades a 2 bits
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // Interrupciones usadas:
    // 0,0	TIM6 para el DAC (audioplayer.c)
    // 0,1	USART3 RX para leer respuestas del modulo bluetooth (bluetooth.c)
    // 1,3	Interrupcion fin de buffer DMA (audioplayer.c)
}

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
    printf("Hard Fault exception.\r\n");
    forever {}
}

void MemManage_Handler(void)
{
    printf("Mem Manage exception.\r\n");
    forever {}
}

void BusFault_Handler(void)
{
    printf("Bus Fault exception.\r\n");
    forever {}
}

void UsageFault_Handler(void)
{
    printf("Usage Fault exception.\r\n");
    forever {}
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}
