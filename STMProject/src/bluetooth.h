#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "global.h"
#include "stm32f10x.h"

#define BT_DEVLCASS 0x200404 // Devclass buscado: Audio headset
#define BT_DEVLCASS_STR "200404" // String para los comandos AT
#define BT_PREF_MAC     "001A0EE5081D" // MAC del headset preferido, se le da prioridad
#define BT_DEFAULT_PIN  "0000" // Debe ser de 4 caracteres numericos

typedef enum {
    BT_NONE,           // Todavia no se verifico la presencia del modulo
    BT_DISCONNECTED,   // Sabemos que esta el modulo
    BT_CONNECTED,      // Estamos conectados al headset (paired+connected)
    BT_STARTEDPLAY,    // Dimos la instruccion de empezar a reproducir pero no tenemos confirmacion
    BT_PLAYING,        // Estamos reproduciendo
    BT_STOPPINGPLAY,   // Dimos la instruccion de parar la reproduccion pero no tenemos confirmacion
                       // Con la confirmacion pasaremos a BT_CONNECTED
} bt_state;

// Configuracion general
void setupBluetooth();

// Se conecta con el headset, puede tardar varios segundos
// Devuelve true si no hubo errores
bool btConnect();

// Funcion de self-test, devuelve true si se encontro el modulo
// Necesita el timer funcionando
bool btTest();

// Empieza/termina comunicacion (llamada) con la entrada analogica
void btStartPlaying();
void btStopPlaying();

// Interrupcion de comunicacion con el modulo bluetooth
void USART3_IRQHandler(void);

#endif
