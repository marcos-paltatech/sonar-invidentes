#ifndef CLI_H
#define CLI_H

typedef enum {
    CMD_SELFTEST,
    CMD_PLAY,
    CMD_BTCONNECT,
    CMD_BTCALL,
    CMD_BTHANG,
    CMD_FLASHMEM,
    CMD_MEMCHECK,
    CMD_QUIT,
    CMD_HELP,
    CMD_INVALID,
    CMD_EMPTY
} cmd_type;

cmd_type readCmd(char* cmd, int len);

void cmdHelp();

#endif
