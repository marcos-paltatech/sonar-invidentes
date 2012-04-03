#ifndef SPI_FLASH_H
#define SPI_FLASH_H

#include <stdint.h>
#include "global.h"

#define FLASH_CMD_READ  0x03 // Leer datos (no importan las paginas)
#define FLASH_CMD_WRITE 0x02 // Escribir pagina
#define FLASH_CMD_BE    0xC7 // Borrar toda la memoria
#define FLASH_CMD_RDSR  0x05 // Leer status register
#define FLASH_CMD_RDID  0x9F // Leer ID de la memoria
#define FLASH_CMD_WREN  0x06 // Write-enable

#define FLASH_PAGE_SIZE     0x100 // 256-byte pages
#define FLASH_PAGE_COUNT    4096  // 1 MiB
#define FLASH_DUMMY_BYTE    0xA5
#define FLASH_WIP_FLAG      0x01

#define FLASH_ID_W25Q80BV   0xEF4014

// Configura SPI para usar la memoria flash
void flashSetup();
// Devuelve el ID de la memoria flash, deberia ser igual a FLASH_ID_W25Q80BV
uint32_t flashGetID();

// Devuelve true si se pudo comunicar con la memoria y el id es el esperado
bool flashTest();

// Escribir una pagina en memoria, addr deberia estar alineado a FLASH_PAGE_SIZE
// Las paginas deben ser borradas antes de ser escritas
void flashWritePage(uint8_t* data, uint16_t len, uint32_t addr);
// Leer cantidad ilimitada de bytes desde addr
void flashReadBuffer(uint8_t* data, uint16_t len, uint32_t addr);
// Borrar toda la memoria
void flashEraseAll();

// Modo para programar la memoria flash via STDIN/STDOUT
void flashProgramMode();
// Checksum de toda la memoria
// La suma de los adler32 de todas las paginas
uint32_t flashFullChecksum();

#endif
