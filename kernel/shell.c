#include "shell.h"
#include "../drivers/screen.h"
#include "../libc/string.h"
#include "../libc/syscalls.h"

void register_command(command_t command) {
    commands[strhash(command.name, NUM_COMMANDS)] = command;
}

void evaluate(const char *user_input) {
    const command_t cmd = commands[strhash(user_input, NUM_COMMANDS)];

    if (cmd.interpreter) cmd.interpreter();
    kprint_colored(SHELL_PROMPT, cyan, black);
}

void init_shell() {
    clear_screen();
    kprint_colored(SHELL_PROMPT, cyan, black);

    register_command((command_t) {"HALT", halt_cpu});
    register_command((command_t) {"CLEAR", clear_screen});
}
