#include "sonarboard.h"

#define ledGPIO	GPIOC
#define btnGPIO	GPIOA
static enum {
	ledCount= 3,
	ledClock= RCC_APB2Periph_GPIOC,
	btnCount= 3,
	btnClock= RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO
};

void SB_Setup()
{
    // Interrupt Setup
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x00);
    // 2 bit priority table
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // Interrupciones usadas:
    // 0,0	TIM6 para el DAC (audioplayer.c)
    // 0,1	USART3 RX para leer respuestas del modulo bluetooth (bluetooth.c)
    // 1,3	Interrupcion fin de buffer DMA (audioplayer.c)
    // 4,4	Interrupcion del boton

	// Setup leds
	//
	RCC_APB2PeriphClockCmd(ledClock, ENABLE);
	GPIO_InitTypeDef gpioConfig;
	gpioConfig.GPIO_Pin= SB_LedG | SB_LedY | SB_LedR;
	gpioConfig.GPIO_Mode= GPIO_Mode_Out_PP;
	gpioConfig.GPIO_Speed= GPIO_Speed_2MHz;
	GPIO_Init(ledGPIO, &gpioConfig);

	// Setup user button
	//
	RCC_APB2PeriphClockCmd(btnClock, ENABLE);
	gpioConfig.GPIO_Pin = SB_Button1;
	gpioConfig.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(btnGPIO, &gpioConfig);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

	EXTI_InitTypeDef extiConfig;
	extiConfig.EXTI_Line= EXTI_Line0;
	extiConfig.EXTI_Mode= EXTI_Mode_Interrupt;
	extiConfig.EXTI_Trigger= EXTI_Trigger_Rising;
	extiConfig.EXTI_LineCmd = ENABLE;
	EXTI_Init(&extiConfig);

	NVIC_InitTypeDef nvicConfig;
	nvicConfig.NVIC_IRQChannel= EXTI0_IRQn;
	nvicConfig.NVIC_IRQChannelPreemptionPriority= 4;
	nvicConfig.NVIC_IRQChannelSubPriority= 4;
	nvicConfig.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicConfig);
}

void SB_LedSet(SB_Led led, bool value)
{
	if(value)
		ledGPIO->BSRR= led;
	else
		ledGPIO->BRR= led;
}

void SB_LedToggle(SB_Led led)
{
	ledGPIO->ODR ^= led;
}
