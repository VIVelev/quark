#ifndef HANDLING
    #define HANDLING

    #include "idt.h"

    /* Struct which aggregates many registers */
    typedef struct {
        uint32_t ds;  /* Data segment selector */
        uint32_t edi, esi, ebp, useless, ebx, edx, ecx, eax;  /* Pushed by pusha */
        uint32_t int_no, err_code;  /* Interrupt number and error code (if applicable) */
        uint32_t eip, cs, eflags, esp, ss;  /* Pushed by the processor automatically */
    } registers_t;

    /* ISR Handler function type */
    typedef void (*ihandler_t)(registers_t *);

    ihandler_t interrupt_handlers[IDT_ENTRIES];
    void register_interrupt_handler(uint8_t index, ihandler_t handler);
    void handle_interrupt(registers_t *r);

    void install_interrupt_handlers();

#endif /* HANDLING */
