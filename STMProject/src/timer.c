#include "timer.h"

#define TIMER_FREQ  100 // 10ms
static uint32_t msecs;

void setupTimer()
{
    // Obtener frecuencia
    RCC_ClocksTypeDef clocks;
    RCC_GetClocksFreq(&clocks);
    uint32_t sysClock= clocks.SYSCLK_Frequency;

    msecs= 0;

    // Iniciar systimer
    SysTick_Config(sysClock/TIMER_FREQ);
}

void SysTick_Handler(void)
{
    msecs += 1000/TIMER_FREQ;
}

uint32_t getMsecs()
{
    return msecs;
}

void sleep(uint32_t msecs)
{
    uint32_t stopTime= getMsecs() + msecs;
    waitWhile(getMsecs() < stopTime);
}
