#include "kernel.h"
#include "../cpu/interrupt_handling.h"
#include "../drivers/keyboard.h"

void main() {
    install_interrupt_handlers();
    __asm__("sti");

    init_keyboard();
}
