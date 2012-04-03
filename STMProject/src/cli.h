#ifndef CLI_H
#define CLI_H

typedef enum {
    CMD_SELFTEST,
    CMD_PLAY,
    CMD_BTCONNECT,
    CMD_QUIT,
    CMD_HELP,
    CMD_INVALID
} cmd_type;

cmd_type readCmd(char* cmd, int len);

void cmdHelp();

#endif
