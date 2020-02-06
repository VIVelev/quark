#include "syscalls.h"

/**
 * Stops the CPU altogether.
 */
void halt_cpu() {
    kprint("\nStopping the CPU. Bye!\n");
    __asm__("hlt");
}
