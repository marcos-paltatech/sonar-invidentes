#ifndef IO_RETARGET_H
#define IO_RETARGET_H

#include "global.h"
#include "stm32f10x.h"

void setupRetargetUSART1();

// Atollic-specific Redefinitions
int _write_r(void *reent, uint16_t fd, const char *ptr, uint32_t len);
int _read_r(void *reent, uint16_t fd, char *ptr, uint32_t len);

// Leer string terminada con \r de largo maximo len
// Devuelve la cantidad de caracteres leidos: a lo sumo len-1
// En string no tiene los caracteres de fin de linea
int readLine(char *ptr, uint16_t len);

#endif
