#ifndef CLI_H
#define CLI_H

#include "sonarboard.h"

typedef enum {
    CMD_SELFTEST,
    CMD_PLAY,
    CMD_SENSORS,
    CMD_BTCONNECT,
    CMD_BTCALL,
    CMD_BTHANG,
    CMD_BTCONFIG,
    CMD_FLASHMEM,
    CMD_MEMCHECK,
    CMD_BATTLEVEL,
    CMD_RESET,
    CMD_HELP,
    CMD_INVALID,
    CMD_EMPTY
} cmd_type;

cmd_type readCmd();

void cmdHelp();

#endif
