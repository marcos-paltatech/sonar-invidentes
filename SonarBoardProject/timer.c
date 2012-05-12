#include "timer.h"

#define TIMER_FREQ  100 // 10ms
static uint32_t msecs;

static uint16_t gLedPeriod; // 0==Off, 0xFFFF=On
static uint32_t gLedLastToggle;
static uint16_t yLedPeriod; // 0==Off, 0xFFFF=On
static uint32_t yLedLastToggle;
static uint16_t rLedPeriod; // 0==Off, 0xFFFF=On
static uint32_t rLedLastToggle;

void timerSetup()
{
    msecs= 0;

    // Obtener frecuencia
    RCC_ClocksTypeDef clocks;
    RCC_GetClocksFreq(&clocks);
    uint32_t sysClock= clocks.SYSCLK_Frequency;

    gLedPeriod= 0;
    gLedLastToggle= 0;
    yLedPeriod= 0;
    yLedLastToggle= 0;
    rLedPeriod= 0;
    rLedLastToggle= 0;

    // Iniciar systimer
    SysTick_Config(sysClock/TIMER_FREQ);
}

// Interrupcion
void SysTick_Handler(void)
{
    // Actualizar el timer
    msecs += 1000/TIMER_FREQ;

    // Blinking de leds
    if(gLedPeriod && gLedPeriod!=0xFFFF && msecs-gLedLastToggle>=gLedPeriod) {
        SB_LedToggle(SB_LedG);
        gLedLastToggle= msecs;
    }
    if(yLedPeriod && yLedPeriod!=0xFFFF && msecs-yLedLastToggle>=yLedPeriod) {
        SB_LedToggle(SB_LedY);
        yLedLastToggle= msecs;
    }
    if(rLedPeriod && rLedPeriod!=0xFFFF && msecs-rLedLastToggle>=rLedPeriod) {
        SB_LedToggle(SB_LedR);
        rLedLastToggle= msecs;
    }
}

uint32_t getMsecs()
{
    return msecs;
}

void sleep(uint32_t msecsTime)
{
    uint32_t stopTime= msecs + msecsTime;
    waitWhile(msecs < stopTime);
}

//
// Funciones para manejar LEDs
//

void SB_LedSet(SB_Led led, bool value)
{
	SB_LedBlinkPeriod(led, (value ? 0xFFFF : 0x0000));
	if(value)
		SB_LedGPIO->BSRR= led;
	else
		SB_LedGPIO->BRR= led;
}

void SB_LedToggle(SB_Led led)
{
	SB_LedGPIO->ODR ^= led;
}

void SB_LedBlinkPeriod(SB_Led led, uint16_t period)
{
	switch(led) {
		case SB_LedG: gLedPeriod= period; break;
		case SB_LedY: yLedPeriod= period; break;
		default:
		case SB_LedR: rLedPeriod= period; break;
	}
}

void SB_LedTest()
{
	uint8_t delay= 75;
	SB_LedSet(SB_LedG, true);
	sleep(delay);
	SB_LedSet(SB_LedY, true);
	sleep(delay);
	SB_LedSet(SB_LedR, true);
	sleep(delay);
	SB_LedSet(SB_LedG, false);
	sleep(delay);
	SB_LedSet(SB_LedY, false);
	sleep(delay);
	SB_LedSet(SB_LedR, false);
	sleep(delay);
}
