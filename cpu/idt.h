#ifndef IDT_H
    #define IDT_H   // IDT stands for "Interrupt Descriptor Table"

    #include "../kernel/utils.h"
    #include "types.h"

    // Kernel Code Segmentation
    #define KERNEL_CS 0x08
    #define IDT_ENTRIES 256    // 1 entry is 8 bytes => 256 * 8 = 2KB in total

    // Interrupt Gate (Handler) struct
    typedef struct {
        uint16_t low_offset;    // offset bits 0..15
        uint16_t high_offset;   // offset bits 16..31
        uint16_t selector;      // a code segment selector in GDT or LDT
        uint8_t always0;        // unused, set to 0

        // First byte
        // Bits 0-3: bits 1110 = decimal 14 = "32 bit interrupt gate"
        // Bit 4: Set to 0 for interrupt gates
        // Bits 6-5: Privilege level of caller (0=kernel..3=user)
        // Bit 7: "Interrupt is present"
        uint8_t flags;
    } __attribute__((packed)) idt_gate_t;

    // A pointer to the array of interrupt handlers (i.e. idt gates).
    // Assembly instruction `lidt` will read it.
    typedef struct {
        uint32_t base;
        uint16_t limit;
    } __attribute__((packed)) idt_register_t;


    // Declare idt gates and register
    idt_gate_t idt[IDT_ENTRIES];
    idt_register_t idt_reg;

    void set_idt_gate(uint8_t index, uint32_t handler);
    void set_idt();

#endif /* IDT_H */
