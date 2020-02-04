#include "idt.h"
#include "../../libc/bitwise.h"

void set_idt_gate(uint8_t index, uint32_t handler) {
    idt[index].low_offset = low_16(handler);
    idt[index].selector = KERNEL_CS;
    idt[index].always0 = 0;
    idt[index].flags = 0x8e;
    idt[index].high_offset = high_16(handler);
}

void set_idt() {
    idt_reg.limit = (uint16_t)(IDT_ENTRIES * sizeof(idt_gate_t) - 1);
    idt_reg.base = (uint32_t) &idt;
    /* Don't make the mistake of loading `&idt`, always load `&idt_reg`. */
    __asm__("lidtl (%0)" : : "r" (&idt_reg));
}
