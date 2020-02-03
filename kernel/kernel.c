#include "../cpu/interrupt_handling.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"

void main() {
    install_interrupt_handlers();
    __asm__ __volatile__("sti");

    // init_timer(100);
    init_keyboard();
}
