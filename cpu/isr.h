#ifndef ISR_H
    #define ISR_H  /* ISR stands for "Interrupt Service Routine" */

    #include "idt.h"

    /* Struct which aggregates many registers */
    typedef struct {
        uint32_t ds;  /* Data segment selector */
        uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* Pushed by pusha */
        uint32_t int_no, err_code;  /* Interrupt number and error code (if applicable) */
        uint32_t eip, cs, eflags, useresp, ss;  /* Pushed by the processor automatically */
    } registers_t;

    /* ISR Handler function type */
    typedef void (*isr_t)(registers_t);

    /* ISRs reserved for CPU exceptions */
    extern void isr0();
    extern void isr1();
    extern void isr2();
    extern void isr3();
    extern void isr4();
    extern void isr5();
    extern void isr6();
    extern void isr7();
    extern void isr8();
    extern void isr9();
    extern void isr10();
    extern void isr11();
    extern void isr12();
    extern void isr13();
    extern void isr14();
    extern void isr15();
    extern void isr16();
    extern void isr17();
    extern void isr18();
    extern void isr19();
    extern void isr20();
    extern void isr21();
    extern void isr22();
    extern void isr23();
    extern void isr24();
    extern void isr25();
    extern void isr26();
    extern void isr27();
    extern void isr28();
    extern void isr29();
    extern void isr30();
    extern void isr31();

    const char *EXCEPTION_MESSAGES[] = {
        "Division By Zero",
        "Debug",
        "Non Maskable Interrupt",
        "Breakpoint",
        "Into Detected Overflow",
        "Out of Bounds",
        "Invalid Opcode",
        "No Coprocessor",

        "Double Fault",
        "Coprocessor Segment Overrun",
        "Bad TSS",
        "Segment Not Present",
        "Stack Fault",
        "General Protection Fault",
        "Page Fault",
        "Unknown Interrupt",

        "Coprocessor Fault",
        "Alignment Check",
        "Machine Check",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",

        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved"
    };

    void setup_isr();

    isr_t interrupt_handlers[IDT_ENTRIES];
    void register_interrupt_handler(uint8_t index, isr_t handler);

    void _isr_handler(registers_t r);
    void _irq_handler(registers_t r);
    void handle_interrupt(registers_t r);

#endif /* ISR_H */
