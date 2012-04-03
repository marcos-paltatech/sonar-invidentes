#include "audioplayer.h"
// DAC1 esta conectado con DMA1 Channel 3
// TIM6 y TIM7 son los timers diseniados para triggear el DAC

#include <stdio.h>
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "audiotracks.h"

// Paginas de memoria en uno de los pcmBuffers
#define PLAYER_BUFFER_PAGES     2
// Tamanio de un pcmBuffer
#define PLAYER_BUFFER_SIZE      (PLAYER_BUFFER_PAGES * FLASH_PAGE_SIZE)

// Direccion base para los regs de los DAC (ver mapa de memoria en la doc)
#define PLAYER_DAC_BASE     0x40007400
// Direccion del registro DAC_DHR8R1: DAC Channel 1, 8-bit right-aligned data
// Va a usarse de destino para el DMA
#define PLAYER_DAC_DHR8R1   (PLAYER_DAC_BASE + 0x10)

// Buffers para el DMA
static uint8_t pcmBuffer1[PLAYER_BUFFER_SIZE];
static uint8_t pcmBuffer2[PLAYER_BUFFER_SIZE];
// Buffer actual (0->pcmBuffer1, 1->pcmBuffer2)
static bool pcmBufferIndex;
// Pagina de memoria actual
static uint16_t pcmCurrentPage;
// Ultima pagina a reproducir
static uint16_t pcmLastPage;

static uint16_t samplingRate= 16000;
static uint8_t channelCount= 1;

// Setear la frecuencia de autoreload de TIM6 en funcion de la freq de sistema
static
bool setAutoReload(TIM_TypeDef* tim, uint32_t rate, uint8_t channels)
{
    // Obtener frecuencia de sistema
    RCC_ClocksTypeDef clocks;
    RCC_GetClocksFreq(&clocks);
    uint32_t sysFreq= clocks.SYSCLK_Frequency;

    // Verificar que el rate divida a la frecuencia del sistema
    if(sysFreq % (rate * channels))
        return false;

    // Setear la frecuencia de autoreload
    TIM_SetAutoreload(tim, sysFreq / (rate * channels));
    return true;
}

static bool playerSetup()
{
    // Setear "Interrupt and exception vectors table"
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x00);
    // Configurar tabla de prioridades a 2 bits
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef nvicConfig;
    // TIM6 interrupt
    nvicConfig.NVIC_IRQChannel= TIM6_DAC_IRQn;
    nvicConfig.NVIC_IRQChannelPreemptionPriority= 0;
    nvicConfig.NVIC_IRQChannelSubPriority= 1;
    nvicConfig.NVIC_IRQChannelCmd= ENABLE;
    NVIC_Init(&nvicConfig);
    // DMA1_Channel3 interrupt
    nvicConfig.NVIC_IRQChannel= DMA1_Channel3_IRQn;
    nvicConfig.NVIC_IRQChannelPreemptionPriority= 1;
    nvicConfig.NVIC_IRQChannelSubPriority= 3;
    nvicConfig.NVIC_IRQChannelCmd= ENABLE;
    NVIC_Init(&nvicConfig);

    // Activar clock de DMA1
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    // Configurar DMA1 Channel 3 para DAC1
    DMA_InitTypeDef dmaConfig;
    dmaConfig.DMA_PeripheralBaseAddr= PLAYER_DAC_DHR8R1;
    dmaConfig.DMA_MemoryBaseAddr= (uint32_t)&pcmBuffer1;
    dmaConfig.DMA_DIR= DMA_DIR_PeripheralDST;
    dmaConfig.DMA_BufferSize= PLAYER_BUFFER_SIZE;
    dmaConfig.DMA_PeripheralInc= DMA_PeripheralInc_Disable;
    dmaConfig.DMA_MemoryInc= DMA_MemoryInc_Enable;
    dmaConfig.DMA_PeripheralDataSize= DMA_PeripheralDataSize_Byte;
    dmaConfig.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    dmaConfig.DMA_Mode= DMA_Mode_Normal;
    dmaConfig.DMA_Priority= DMA_Priority_High;
    dmaConfig.DMA_M2M= DMA_M2M_Disable;
    DMA_Init(DMA1_Channel3, &dmaConfig);
    //DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);
    DMA_Cmd(DMA1_Channel3, ENABLE);

    // Activar clock DAC1
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
    // Configurar DAC1
    DAC_InitTypeDef dacConfig;
    DAC_StructInit(&dacConfig);
    dacConfig.DAC_Trigger= DAC_Trigger_T6_TRGO; // TIM6 trigger
    dacConfig.DAC_WaveGeneration= DAC_WaveGeneration_None;
    // No necesitamos el buffer si tenemos alta impedancia de entrada
    dacConfig.DAC_OutputBuffer= DAC_OutputBuffer_Disable;
    DAC_Init(DAC_Channel_1, &dacConfig);
    DAC_Cmd(DAC_Channel_1, ENABLE);
    // Activar DMA para el DAC
    DAC_DMACmd(DAC_Channel_1, ENABLE);

    // Activar clock TIM6
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    // Configurar el TIM6
    TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);
    if(!setAutoReload(TIM6, samplingRate, channelCount)) {
        printf("playerSetup: No pude setear autoreload\r\n");
        return false;
    }
    // Activar interrupcion para TIM6
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);

    // Configurar memoria
    flashSetup();

    return true;
}

inline static
uint8_t* playerGetPcmBuffer()
{
    return pcmBufferIndex ? pcmBuffer2 : pcmBuffer1;
}

inline static
void playerReadData()
{
    flashReadBuffer(playerGetPcmBuffer(), PLAYER_BUFFER_SIZE, pcmCurrentPage * FLASH_PAGE_SIZE);

    pcmCurrentPage += PLAYER_BUFFER_PAGES;
}

static
void playerDMATransfer()
{
    // Verificamos si hay que terminar
    if(pcmCurrentPage > pcmLastPage)
        playerStop();

    // Deshabilitar DMA para configurarlo
    DMA1_Channel3->CCR= 0;
    // Seteamos la cantidad de bytes a transmitir
    DMA1_Channel3->CNDTR= PLAYER_BUFFER_SIZE;
    // Seteamos como destino el registro del DAC
    DMA1_Channel3->CPAR= PLAYER_DAC_DHR8R1;
    // Seteamos como origen la direccion de memoria del buffer
    DMA1_Channel3->CMAR= (uint32_t)playerGetPcmBuffer();
    // Empezamos la transmision DMA
    DMA1_Channel3->CCR= 0x2093;

    // Toggle entre buffers
    pcmBufferIndex = !pcmBufferIndex;
    // DMA ya esta andando, ahora cargamos el proximo buffer
    playerReadData();
}

// pageCount debe ser multiplo de PLAYER_BUFFER_PAGES;
void playerPlay(uint32_t page, uint32_t pageCount)
{
    pcmCurrentPage= page;
    pcmLastPage= page + pageCount - 1;

    // Es necesario configurar DMA, TIM6, etc. en cada play
    // porque al pararlos en playerStop se desconfiguran
    if(!playerSetup())
        return;

    // Activar el timer
    TIM_Cmd(TIM6, ENABLE);

    // Seleccionamos pcmBuffer1 y lo llenamos
    pcmBufferIndex= 0;
    playerReadData();

    // Empezamos la transmision DMA de pcmBuffer1
    // Cuando se termine se va a llamar a DMA1_Channel3_IRQHandler()
    playerDMATransfer();
}

void playerPlayTrack(uint8_t trackId)
{
    if(trackId == 0xFF) {
        printf("Seleccionar track track:\r\n");
        for(int i=0; i<TRACKS_COUNT; i++) {
            const uint16_t start= TRACKS_PAGES[i];
            const uint16_t len= TRACKS_PAGES[i+1]-TRACKS_PAGES[i];
            printf("  - Track %2d | Start %3d, Length %3d.\r\n", i, start, len);
        }
        char c;
        do {
            _read_r(0, 0, &c, 1);
            trackId= c - '0';
        } while(trackId < 0 || trackId >= TRACKS_COUNT);
        printf("Reproduciendo track %d.\r\n", trackId);
    }
    playerPlay(TRACKS_PAGES[trackId], TRACKS_PAGES[trackId+1]-TRACKS_PAGES[trackId]);
}

void playerStop()
{
    // Desactivar el timer que mueve al DAC
    TIM_ITConfig(TIM6, TIM_IT_Update, DISABLE);
    TIM_Cmd(TIM6, DISABLE);
    // Desactivar DMA
    DMA1_Channel3->CCR= 0;
    printf("Stopped playing.\r\n");
}


// Interrupcion que se ejecuta cuando el DMA1 Channel 3 termina
// de transmitir los datos en memoria.
// Cuando pasa esto empezamos el DMA de otro buffer ya cargado,
// y cargamos el que se utilizo. Asi siempre hay un buffer listo para
// transmitir.
void DMA1_Channel3_IRQHandler()
{
    if(DMA_GetITStatus(DMA1_IT_TC3) == RESET)
        return;

    playerDMATransfer();

    DMA_ClearITPendingBit(DMA1_IT_TC3);
    //printf("DMA %d\r\n", pcmBufferIndex);
}

// Interrupcion del TIM6 al DAC
// Esta interrupcion es la que le indica al DAC que tiene que pedirle
// datos al engine DMA, y se ejecuta una vez por sample de audio.
void TIM6_DAC_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
}
