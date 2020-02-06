#include "syscalls.h"
#include "../drivers/screen.h"

/**
 * Stops the CPU altogether.
 */
void halt_cpu() {
    kprint("\nStopping the CPU. Bye!\n");
    __asm__("hlt");
}
