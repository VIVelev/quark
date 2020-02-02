#include "interrupt_handling.h"
#include "isr.h"
#include "irq.h"

void register_interrupt_handler(uint8_t index, ihandler_t handler) {
    interrupt_handlers[index] = handler;
}

/**
 * Public Interrupt Handler method.
 * 
 * @param r accumulated registers
 */
void handle_interrupt(registers_t r) {
    if (r.int_no < 32)
        handle_isr(r);
    else
        handle_irq(r);
}

void install_interrupt_handlers() {
    install_isr();
    install_irq();
    set_idt();
}
