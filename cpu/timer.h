#ifndef TIMER_H
    #define TIMER_H

    #include "types.h"

    /* The PIT contains a crystal oscillator which emits a signal 1193182 hz. */
    #define HARDWARE_PIT_FREQ 1193182

    #define REG_PIT_CTRL 0x43
    #define REG_PIT_DATA_CHANNEL_0 0x40

    void init_timer(uint32_t frequency);

#endif /* TIMER_H */