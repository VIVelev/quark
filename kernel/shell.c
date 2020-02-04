#include "shell.h"
#include "../drivers/screen.h"
#include "../libc/string.h"

void init_shell() {
    clear_screen();
    kprint_colored(SHELL_PROMPT, cyan, black);
}

void evaluate(const char *user_input) {
    if (strcmp(user_input, "HALT") == 0) {
        kprint("\nStopping the CPU. Bye!\n");
        __asm__("hlt");

    }else if (strcmp(user_input, "CLEAR") == 0) {
        clear_screen();
    }

    kprint_colored(SHELL_PROMPT, cyan, black);
}
