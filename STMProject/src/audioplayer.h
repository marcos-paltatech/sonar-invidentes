#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "global.h"
#include "spi_flash.h"

void playerPlay(uint32_t page, uint32_t pageCount);
void playerStop();

// Funciones usadas por DMA1_Channel3_IRQHandler()
void playerDMATransfer();

#endif
