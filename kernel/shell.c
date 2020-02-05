#include "shell.h"
#include "../drivers/screen.h"
#include "../libc/string.h"

/* TODO: implement hash-map for command_name to command_interpreter */

void _halt_cpu();


void register_command(command_t command) {
    commands[strhash(command.name, NUM_COMMANDS)] = command;
}

void evaluate(const char *user_input) {
    cmd_interpreter_t interpreter = commands[strhash(user_input, NUM_COMMANDS)].interpreter;

    if (interpreter) interpreter();
    kprint_colored(SHELL_PROMPT, cyan, black);
}

void _halt_cpu() {
    kprint("\nStopping the CPU. Bye!\n");
    __asm__("hlt");
}

void init_shell() {
    clear_screen();
    kprint_colored(SHELL_PROMPT, cyan, black);

    register_command((command_t) {"HALT", _halt_cpu});
    register_command((command_t) {"CLEAR", clear_screen});
}
