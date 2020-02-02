#include "../cpu/interrupt_handling.h"

void main() {
    install_interrupt_handlers();
    /* Test the interrupts */
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
}
