#include "kernel.h"
#include "../cpu/interrupt/handling.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"

void kmain() {
    /* Enable interrupts */
    __asm__("sti");
    /* Handle interrupts */
    install_interrupt_handlers();

    /* Init */
    init_timer(100);
    init_keyboard();
}
