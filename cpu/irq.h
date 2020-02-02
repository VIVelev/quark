#ifndef IRQ_H
    #define IRQ_H  /* IRQ stands for "Interrupt ReQuest". */

    #include "isr.h"

    #define REG_MASTER_PIC_CTRL 0x20
    #define REG_MASTER_PIC_DATA 0x21

    #define REG_SLAVE_PIC_CTRL 0xA0
    #define REG_SLAVE_PIC_DATA 0xA1

    /* IRQ definitions */
    extern void irq0();
    extern void irq1();
    extern void irq2();
    extern void irq3();
    extern void irq4();
    extern void irq5();
    extern void irq6();
    extern void irq7();
    extern void irq8();
    extern void irq9();
    extern void irq10();
    extern void irq11();
    extern void irq12();
    extern void irq13();
    extern void irq14();
    extern void irq15();

    void install_irq();
    void handle_irq(registers_t r);

#endif /* IRQ_H */
