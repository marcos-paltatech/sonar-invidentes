#include "stm32f10x_it.h"
#include "global.h"
#include <stdio.h>

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
