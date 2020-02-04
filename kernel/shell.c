#include "shell.h"
#include "../drivers/screen.h"
#include "../libc/string.h"

void init_shell() {
    clear_screen();
    kprint(SHELL_PROMPT);
}

void evaluate(char *user_input) {
    if (strcmp(user_input, "HALT") == 0) {
        kprint("\nStopping the CPU. Bye!\n");
        __asm__("hlt");

    }else if (strcmp(user_input, "CLEAR") == 0) {
        clear_screen();
    }

    kprint(SHELL_PROMPT);
}
