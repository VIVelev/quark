#ifndef SHELL_H
#define SHELL_H

#include "../cpu/type.h"

#define SHELL_PROMPT "quark> "
#define NUM_COMMANDS 256

typedef void (*cmd_interpreter_t)();

typedef struct {
    char name[256];
    cmd_interpreter_t interpreter;
} command_t;

command_t commands[NUM_COMMANDS];
void register_command(command_t command);
void evaluate(const char *user_input);

void init_shell();

#endif /* SHELL_H */
