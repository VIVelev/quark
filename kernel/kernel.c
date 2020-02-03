#include "../cpu/interrupt_handling.h"
#include "../cpu/timer.h"

void main() {
    install_interrupt_handlers();
    __asm__ __volatile__("sti");

    init_timer(100);
}
