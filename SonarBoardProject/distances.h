#ifndef DISTANCES_H
#define DISTANCES_H

#include "sonarboard.h"

// Frecuencia de medicion: 250ms
#define DIST_FREQ	  4

void distSetup();

void distStartMeasuring(bool oneShot);
void distStopMeasuring();

void TIM2_IRQHandler();

#endif
