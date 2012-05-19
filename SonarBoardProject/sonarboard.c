#include "sonarboard.h"

static enum {
	ledCount= 3,
	ledClock= RCC_APB2Periph_GPIOC,
	btnCount= 3,
	btnClock= RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,
	adcClock= RCC_APB2Periph_GPIOC | RCC_APB2Periph_ADC1
};

static void setupBattADC()
{
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); // 3 Mhz
	RCC_APB2PeriphClockCmd(adcClock, ENABLE);

	// PC0
	GPIO_InitTypeDef gpioConfig;
	gpioConfig.GPIO_Mode= GPIO_Mode_AIN;
	gpioConfig.GPIO_Pin= GPIO_Pin_0;
	GPIO_Init(GPIOC, &gpioConfig);

	ADC_InitTypeDef adcConfig;
	adcConfig.ADC_Mode= ADC_Mode_Independent;
	adcConfig.ADC_ScanConvMode= DISABLE;
	adcConfig.ADC_ContinuousConvMode= DISABLE;
	adcConfig.ADC_ExternalTrigConv= ADC_ExternalTrigConv_None;
	adcConfig.ADC_DataAlign= ADC_DataAlign_Right;
	adcConfig.ADC_NbrOfChannel= 1;
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_239Cycles5);
	ADC_Init(ADC1, &adcConfig);
	ADC_Cmd(ADC1, ENABLE);

	ADC_ResetCalibration(ADC1);
	waitWhile(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	waitWhile(ADC_GetCalibrationStatus(ADC1));
}

void SB_Setup()
{
    // Interrupt Setup
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x00);
    // 2 bit priority table
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // Interrupciones usadas:
    // 0,0	TIM6 para el DAC (audioplayer.c)
    // 0,1	USART3 RX para leer respuestas del modulo bluetooth (bluetooth.c)
    // 0,2  System timer
    // 1,3	Interrupcion fin de buffer DMA (audioplayer.c)
    // 3,3	Interrupcion del boton

	// Setup leds
	//
	RCC_APB2PeriphClockCmd(ledClock, ENABLE);
	GPIO_InitTypeDef gpioConfig;
	gpioConfig.GPIO_Pin= SB_LedG | SB_LedY | SB_LedR;
	gpioConfig.GPIO_Mode= GPIO_Mode_Out_PP;
	gpioConfig.GPIO_Speed= GPIO_Speed_2MHz;
	GPIO_Init(SB_LedGPIO, &gpioConfig);

	// Setup del ADC para nivel de bateria
	setupBattADC();

	// Setup user button
	//
	RCC_APB2PeriphClockCmd(btnClock, ENABLE);
	gpioConfig.GPIO_Pin = SB_Button1;
	gpioConfig.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(SB_ButtonGPIO, &gpioConfig);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

	EXTI_InitTypeDef extiConfig;
	extiConfig.EXTI_Line= EXTI_Line0;
	extiConfig.EXTI_Mode= EXTI_Mode_Interrupt;
	extiConfig.EXTI_Trigger= EXTI_Trigger_Rising_Falling;
	extiConfig.EXTI_LineCmd = ENABLE;
	EXTI_Init(&extiConfig);

	NVIC_InitTypeDef nvicConfig;
	nvicConfig.NVIC_IRQChannel= EXTI0_IRQn;
	nvicConfig.NVIC_IRQChannelPreemptionPriority= 3;
	nvicConfig.NVIC_IRQChannelSubPriority= 3;
	nvicConfig.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicConfig);

    // Setup del system timer
	//
    timerSetup();
    // Seteamos la prioridad a 0,2
    NVIC_SetPriority(SysTick_IRQn, (!0 << 2));
}

bool SB_ButtonState(SB_Button button)
{
	return GPIO_ReadInputDataBit(SB_ButtonGPIO, button);
}

uint16_t SB_GetBatteryLevel()
{
	ADC_Cmd(ADC1, ENABLE);
	// Empezar conversion
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    waitWhile(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
    uint16_t value= ADC_GetConversionValue(ADC1);
    ADC_Cmd(ADC1, DISABLE);

    // 4095 -> 3.3v en el ADC -> ~19.4v de entrada
    value= (value * 19400) / 4095;

    return value;
}
