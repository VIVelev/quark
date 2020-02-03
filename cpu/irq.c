#include "irq.h"
#include "ports.h"

void install_irq() {
    /* Remap the PIC */
    port_byte_out(REG_MASTER_PIC_CTRL, 0x11);
    port_byte_out(REG_SLAVE_PIC_CTRL, 0x11);

    port_byte_out(REG_MASTER_PIC_DATA, 0x20);
    port_byte_out(REG_SLAVE_PIC_DATA, 0x28);

    port_byte_out(REG_MASTER_PIC_DATA, 0x04);
    port_byte_out(REG_SLAVE_PIC_DATA, 0x02);

    port_byte_out(REG_MASTER_PIC_DATA, 0x01);
    port_byte_out(REG_SLAVE_PIC_DATA, 0x01);

    port_byte_out(REG_MASTER_PIC_DATA, 0x0);
    port_byte_out(REG_SLAVE_PIC_DATA, 0x0); 


    /* Install the IRQs */
    set_idt_gate(32, (uint32_t) irq0);
    set_idt_gate(33, (uint32_t) irq1);
    set_idt_gate(34, (uint32_t) irq2);
    set_idt_gate(35, (uint32_t) irq3);
    set_idt_gate(36, (uint32_t) irq4);
    set_idt_gate(37, (uint32_t) irq5);
    set_idt_gate(38, (uint32_t) irq6);
    set_idt_gate(39, (uint32_t) irq7);
    set_idt_gate(40, (uint32_t) irq8);
    set_idt_gate(41, (uint32_t) irq9);
    set_idt_gate(42, (uint32_t) irq10);
    set_idt_gate(43, (uint32_t) irq11);
    set_idt_gate(44, (uint32_t) irq12);
    set_idt_gate(45, (uint32_t) irq13);
    set_idt_gate(46, (uint32_t) irq14);
    set_idt_gate(47, (uint32_t) irq15);
}

void handle_irq(registers_t r) {
    /**
     * After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again.
     */
    if (r.int_no >= 40)
        port_byte_out(REG_SLAVE_PIC_CTRL, 0x20);  /* slave */
    port_byte_out(REG_MASTER_PIC_CTRL, 0x20);  /* master */

    if (interrupt_handlers[r.int_no] != 0)
        interrupt_handlers[r.int_no](r);
}
