#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "global.h"
#include "spi_flash.h"

void playerPlay(uint32_t page, uint32_t pageCount);

// Reproduce un track de los listados en audiotracks.h
// Si trackId==255, se muestra un menu para elegir track
void playerPlayTrack(uint8_t trackId);

void playerStop();

// Interrupciones usadas
void DMA1_Channel3_IRQHandler(void);
void TIM6_DAC_IRQHandler(void);

#endif
