#include "shell.h"
#include "../drivers/screen.h"
#include "../libc/string.h"

/* TODO: implement hash-map for command_name to command_interpreter */

void _halt_cpu();


void register_command(uint16_t index, command_t command) {
    commands[index] = command;
}

void evaluate(const char *user_input) {
    for (uint16_t i = 0; i < 5; i++) {
        if (strcmp(user_input, commands[i].name) == 0) {
            commands[i].interpreter();
            break;
        }
    }

    kprint_colored(SHELL_PROMPT, cyan, black);
}

void _halt_cpu() {
    kprint("\nStopping the CPU. Bye!\n");
    __asm__("hlt");
}

void init_shell() {
    clear_screen();
    kprint_colored(SHELL_PROMPT, cyan, black);

    register_command(0, (command_t) {"HALT", _halt_cpu});
    register_command(1, (command_t) {"CLEAR", clear_screen});
}
