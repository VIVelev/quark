#include "isr.h"

void setup_isr() {
    set_idt_gate(0, (uint32_t) isr0);
    set_idt_gate(1, (uint32_t) isr1);
    set_idt_gate(2, (uint32_t) isr2);
    set_idt_gate(3, (uint32_t) isr3);
    set_idt_gate(4, (uint32_t) isr4);
    set_idt_gate(5, (uint32_t) isr5);
    set_idt_gate(6, (uint32_t) isr6);
    set_idt_gate(7, (uint32_t) isr7);
    set_idt_gate(8, (uint32_t) isr8);
    set_idt_gate(9, (uint32_t) isr9);
    set_idt_gate(10, (uint32_t) isr10);
    set_idt_gate(11, (uint32_t) isr11);
    set_idt_gate(12, (uint32_t) isr12);
    set_idt_gate(13, (uint32_t) isr13);
    set_idt_gate(14, (uint32_t) isr14);
    set_idt_gate(15, (uint32_t) isr15);
    set_idt_gate(16, (uint32_t) isr16);
    set_idt_gate(17, (uint32_t) isr17);
    set_idt_gate(18, (uint32_t) isr18);
    set_idt_gate(19, (uint32_t) isr19);
    set_idt_gate(20, (uint32_t) isr20);
    set_idt_gate(21, (uint32_t) isr21);
    set_idt_gate(22, (uint32_t) isr22);
    set_idt_gate(23, (uint32_t) isr23);
    set_idt_gate(24, (uint32_t) isr24);
    set_idt_gate(25, (uint32_t) isr25);
    set_idt_gate(26, (uint32_t) isr26);
    set_idt_gate(27, (uint32_t) isr27);
    set_idt_gate(28, (uint32_t) isr28);
    set_idt_gate(29, (uint32_t) isr29);
    set_idt_gate(30, (uint32_t) isr30);
    set_idt_gate(31, (uint32_t) isr31);

    set_idt();  /* Load with ASM */
}

void register_interrupt_handler(uint8_t index, isr_t handler) {
    interrupt_handlers[index] = handler;
}

void _isr_handler(registers_t r) {
    kprint("Received interrupt: ");

    char s[3];
    int_to_ascii(r.int_no, s);
    kprint(s);

    kprint("\n");
    kprint(EXCEPTION_MESSAGES[r.int_no]);
    kprint("\n");
}

void _irq_handler(registers_t r) {
    /**
     * After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again.
     */
    if (r.int_no >= 40)
        port_byte_out(0xA0, 0x20);  /* slave */
    port_byte_out(0x20, 0x20);  /* master */

    if (interrupt_handlers[r.int_no] != 0)
        interrupt_handlers[r.int_no](r);
}

/**
 * Public Interrupt Handler method.
 * 
 * @param r accumulated registers
 */
void handle_interrupt(registers_t r) {
    if (r.int_no < 32)
        _isr_handler(r);
    else
        _irq_handler(r);
}
