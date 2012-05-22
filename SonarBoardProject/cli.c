#include "cli.h"

#include <string.h>
#include "io_retarget.h"

static enum { cmdLen= 20 }; // can't use static const int here
static char cmdBuffer[cmdLen];

cmd_type readCmd()
{
    putchar('>'); putchar(' ');
    fflush(0);
    int readLen= readLine(cmdBuffer, cmdLen);

    cmd_type type;

    if(!strncasecmp("selftest", cmdBuffer, readLen))
        type= CMD_SELFTEST;
    else if(!strncasecmp("play", cmdBuffer, readLen))
        type= CMD_PLAY;
    else if(!strncasecmp("sensors", cmdBuffer, readLen))
        type= CMD_SENSORS;
    else if(!strncasecmp("btconnect", cmdBuffer, readLen))
        type= CMD_BTCONNECT;
    else if(!strncasecmp("btcall", cmdBuffer, readLen))
        type= CMD_BTCALL;
    else if(!strncasecmp("bthang", cmdBuffer, readLen))
        type= CMD_BTHANG;
    else if(!strncasecmp("btconfig", cmdBuffer, readLen))
        type= CMD_BTCONFIG;
    else if(!strncasecmp("flashmem", cmdBuffer, readLen))
        type= CMD_FLASHMEM;
    else if(!strncasecmp("memcheck", cmdBuffer, readLen))
        type= CMD_MEMCHECK;
    else if(!strncasecmp("battlevel", cmdBuffer, readLen))
        type= CMD_BATTLEVEL;
    else if(!strncasecmp("reset", cmdBuffer, readLen))
        type= CMD_RESET;
    else if(!strncasecmp("help", cmdBuffer, readLen) || !strncasecmp("?", cmdBuffer, readLen))
        type= CMD_HELP;
    else if(!strncasecmp("", cmdBuffer, readLen))
        type= CMD_EMPTY;
    else
        type= CMD_INVALID;

    return type;
}

void cmdHelp()
{
    printf("Comandos:\r\n");
    printf("  selftest   Verificar hardware/software.\r\n");
    printf("  play       Reproducir un track.\r\n");
    printf("  sensors    Muestra informacion de los sensores.\r\n");
    printf("  btconnect  Establecer conexion por bluetooth y llamar al headset.\r\n");
    printf("  btcall     Empezar a transmitir audio por bluetooth.\r\n");
    printf("  bthang     Terminar de transmitir audio por bluetooth.\r\n");
    printf("  btconfig   Configuracion persistente del modulo bluetooth.\r\n");
    printf("  flashmem   Entrar en modo para programar memoria flash.\r\n");
    printf("  memcheck   Calcular y mostrar checksum total de memoria flash.\r\n");
    printf("  battlevel  Muestra el voltaje de la bateria.\r\n");
    printf("  reset      Software reset.\r\n");
    printf("  help/?     Esta ayuda.\r\n");
    printf("\r\n");
}
