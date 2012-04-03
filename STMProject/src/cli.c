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
    else if(!strncasecmp("quit", cmd, readLen))
        type= CMD_QUIT;
    else if(!strncasecmp("help", cmd, readLen) || !strncasecmp("?", cmd, readLen))
        type= CMD_HELP;
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
    printf("  quit       Terminar.\r\n");
    printf("  help/?     Esta ayuda.\r\n");
    printf("\r\n");
}
