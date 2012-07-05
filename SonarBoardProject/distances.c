#include "distances.h"
#include "srf02_sensor.h"

#include "audioplayer.h"

#define ITER 3
#define VERY_CLOSE_DIST 80 //80 cms

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
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}

void distStopMeasuring()
{
    // Desactivar interrupcion para TIM2
    TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
    TIM_Cmd(TIM2, DISABLE);
}


uint16_t dist(uint16_t vals[], int count)
{
	//printf("Entro a dist2\r\n");
	uint16_t max = vals[0];
	uint16_t min = vals[0];
	int total = vals[0];
	int umbral = 50;

	for (int i=1; i<count; i++)
	{
		total += vals[i];
		if (vals[i]<min) min = vals[i];
		if (vals[i]>max) max = vals[i];
	}

	if ((max - min) > umbral)
		return 0; // error de medicion, probablemente <~ 20cm
	else
		return total/count;
}


void modoContinuo(uint16_t mediciones[])
{
	int pfrase=0;
	uint8_t frase[6];

	if (dist(&mediciones[0], ITER) < VERY_CLOSE_DIST)
	{
		printf("Izq= %d\r\n", dist(&mediciones[0], ITER));
		frase[pfrase++] = 1; //left
		//frase[pfrase++] = 6;
	}

	if (dist(&mediciones[3], ITER) < VERY_CLOSE_DIST)
	{
		printf("Frente= %d\r\n", dist(&mediciones[3], ITER));
		frase[pfrase++] = 0; //front
		//frase[pfrase++] = 6;
	}

	if (dist(&mediciones[6], ITER) < VERY_CLOSE_DIST)
	{
		printf("Der= %d\r\n", dist(&mediciones[6], ITER));
		frase[pfrase++] = 2; //right
		//frase[pfrase++] = 6;
	}

	//printf("Tiempo total de calculo %d ms.\r\n", getMsecs()-start);

	if (pfrase>0)
	{
		frase[pfrase++] = 6; // muy cerca!
		playerPlayTracks(frase, pfrase);
	}
}

// calcula el codigo de la grabacion correspondiente
// a la distancia
int codigo_palabra(int distancia)
{
	if (distancia<=50)
		return 6; // very close
	else if (distancia>50 && distancia<=150)
		return 8; // 1 meter
	else if (distancia>150 && distancia<=250)
		return 9; // 2 meter
	else if (distancia>250 && distancia<=350)
		return 10; // 3 meter
	else if (distancia>350 && distancia<=450)
		return 11; // 4 meter
	else if (distancia>450 && distancia<=550)
		return 12; // 5 meter
	else if (distancia>550 && distancia<=650)
		return 13; // 6 meter
	else if (distancia>650 && distancia<=750)
		return 14; // 7 meter
	else if (distancia>750 && distancia<=850)
		return 15; // 8 meter
	else if (distancia>850 && distancia<=950)
		return 16; // 9 meter
	else if (distancia>950 && distancia<=1050)
		return 17; // 10 meter
	else if (distancia>1050)
		return 4; // far
}

void modoPanorama(uint16_t mediciones[])
{
	int pfrase=0;
	uint8_t frase[6];

	frase[pfrase++] = 1; //left
	frase[pfrase++] = codigo_palabra(dist(&mediciones[0], ITER));
	frase[pfrase++] = 0; //front
	frase[pfrase++] = codigo_palabra(dist(&mediciones[3], ITER));
	frase[pfrase++] = 2; //right
	frase[pfrase++] = codigo_palabra(dist(&mediciones[6], ITER));

	playerPlayTracks(frase, pfrase);
}

void TIM2_IRQHandler()
{
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) == RESET)
    	return;

    uint32_t start= getMsecs();
    srf02_setup();

    //printf("A %d ms.\r\n", getMsecs()-start);

    // Hago 3(ITER) series de mediciones
    uint16_t mediciones[3 * ITER];
    int i;
    for(i=0; i<ITER; i++)
    {
		srf02_setCommand(SENS_LEFT);
		srf02_setCommand(SENS_RIGHT);
		sleep(60);
		mediciones[i] = srf02_getResult(SENS_LEFT); //izquierda
		mediciones[i+ITER*2] = srf02_getResult(SENS_RIGHT); //derecha

		//printf("B %d ms.\r\n", getMsecs()-start);
		//sleep(60);
		//printf("C %d ms.\r\n", getMsecs()-start);

		srf02_setCommand(SENS_FRONT);
		sleep(60);
		mediciones[i+ITER] = srf02_getResult(SENS_FRONT); //centro


    }
    printf("i= %d\r\n", i);
    for (int i=0; i<12; i++)
    {
    	printf("Mediciones[%d] = %d\r\n", i, mediciones[i]);
    }

    // selecciona la forma de comunicar las mediciones
    if (oneShotMode)
    	modoPanorama(mediciones);
    else
    	modoContinuo(mediciones);

	//printf("D %d ms.\r\n", getMsecs()-start);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, DISABLE);

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

    if(oneShotMode) {
    	oneShotMode= false;
    	distStopMeasuring();
    }
}

