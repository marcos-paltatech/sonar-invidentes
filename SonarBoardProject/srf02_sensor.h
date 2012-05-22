#ifndef SRF02_SENSOR_H
#define SRF02_SENSOR_H

#include "sonarboard.h"

// Direccion del master
#define SENS_MASTER_ADDRESS  0x20

#define SENS_I2C_FREQ  200000

// Lista de sensores en el bus
#define SENS_FRONT    0xE0
#define SENS_LEFT     0xE4
#define SENS_RIGHT    0xE6
// ...
// Agregar los nuevos sensores aca


/**
 * Lee la última medición realizada por el sensor.
 * Se debe invocar 16mS después de haber enviado el comando de medición
 *
 * uint8_t sensorAddr: Dirección del sensor
 */
uint16_t srf02_getResult(uint8_t sensorAddr);


/**
 * Setea una nueva dirección a un determinado sensor.
 * El sensor debe ser el unico dispositivo en el bus al momento
 * de setear la nueva dirección
 *
 * uint8_t old: Dirección del sensor que se desea setear.
 * uint8_t new: Nueva dirección.
 */
void srf02_setAddress(uint8_t old, uint8_t new);

/**
 * Inicializa el bus I2C
 */
void srf02_setup();

/**
 * Envía el comando de medición al sensor correspondiente.
 *
 * uint8_t sensorAddr: Dirección de sensor destino.
 */
void srf02_setCommand(uint8_t sensorAddr);


#endif /* SRF02_SENSOR_H */
