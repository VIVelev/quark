#include "../cpu/isr.h"

void main() {
    install_isr();
    /* Test the interrupts */
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
}
