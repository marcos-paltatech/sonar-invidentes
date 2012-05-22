#include "distances.h"
#include "srf02_sensor.h"

static bool oneShotMode= false;

void distSetup()
{
    NVIC_InitTypeDef nvicConfig;
    // TIM2 interrupt
    nvicConfig.NVIC_IRQChannel= TIM2_IRQn;
    nvicConfig.NVIC_IRQChannelPreemptionPriority= 3;
    nvicConfig.NVIC_IRQChannelSubPriority= 2;
    nvicConfig.NVIC_IRQChannelCmd= ENABLE;
    NVIC_Init(&nvicConfig);

    // Activar clock TIM2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // Configurar el TIM2
    TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);

    RCC_ClocksTypeDef clocks;
    RCC_GetClocksFreq(&clocks);

    TIM_TimeBaseInitTypeDef timConfig;
    timConfig.TIM_Prescaler = clocks.SYSCLK_Frequency / 1e3; // Prescaler 24000 -> 1 Khz
    timConfig.TIM_CounterMode = TIM_CounterMode_Up;
    timConfig.TIM_Period = (clocks.SYSCLK_Frequency / timConfig.TIM_Prescaler) / DIST_FREQ;
    timConfig.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM2, &timConfig);
}

void distStartMeasuring(bool oneShot)
{
	oneShotMode= oneShot;
	TIM_Cmd(TIM2, ENABLE);
    // Activar interrupcion para TIM2
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}

void distStopMeasuring()
{
    // Desactivar interrupcion para TIM2
    TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
    TIM_Cmd(TIM2, DISABLE);
}

void TIM2_IRQHandler()
{
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) == RESET)
    	return;

	srf02_setCommand(SENS_LEFT);
	srf02_setCommand(SENS_RIGHT);
	srf02_setCommand(SENS_FRONT);
	sleep(60);
	uint16_t dl= srf02_getResult(SENS_LEFT);
	uint16_t df= srf02_getResult(SENS_FRONT);
	uint16_t dr= srf02_getResult(SENS_RIGHT);

	printf("%d %d %d\r\n", dl, df, dr);

    if(oneShotMode) {
    	oneShotMode= false;
    	distStopMeasuring();
    }

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

