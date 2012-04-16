#include "cli.h"

#include <stdio.h>
#include <string.h>
#include "io_retarget.h"

cmd_type readCmd(char* cmd, int len)
{
    putchar('>'); putchar(' ');
    fflush(0);
    int readLen= readLine(cmd, len);

    cmd_type type;

    if(!strncasecmp("selftest", cmd, readLen))
        type= CMD_SELFTEST;
    else if(!strncasecmp("play", cmd, readLen))
        type= CMD_PLAY;
    else if(!strncasecmp("btconnect", cmd, readLen))
        type= CMD_BTCONNECT;
    else if(!strncasecmp("btcall", cmd, readLen))
        type= CMD_BTCALL;
    else if(!strncasecmp("bthang", cmd, readLen))
        type= CMD_BTHANG;
    else if(!strncasecmp("flashmem", cmd, readLen))
        type= CMD_FLASHMEM;
    else if(!strncasecmp("memcheck", cmd, readLen))
        type= CMD_MEMCHECK;
    else if(!strncasecmp("quit", cmd, readLen))
        type= CMD_QUIT;
    else if(!strncasecmp("reset", cmd, readLen))
        type= CMD_RESET;
    else if(!strncasecmp("help", cmd, readLen) || !strncasecmp("?", cmd, readLen))
        type= CMD_HELP;
    else if(!strncasecmp("", cmd, readLen))
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
    printf("  btconnect  Establecer conexion por bluetooth y llamar al headset.\r\n");
    printf("  btcall     Empezar a transmitir audio por bluetooth.\r\n");
    printf("  bthang     Terminar de transmitir audio por bluetooth.\r\n");
    printf("  flashmem   Entrar en modo para programar memoria flash.\r\n");
    printf("  memcheck   Calcular y mostrar checksum total de memoria flash.\r\n");
    printf("  quit       Terminar.\r\n");
    printf("  reset      Software reset.\r\n");
    printf("  help/?     Esta ayuda.\r\n");
    printf("\r\n");
}
