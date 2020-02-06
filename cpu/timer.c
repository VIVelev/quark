#include "timer.h"
#include "port.h"
#include "interrupt/handling.h"
#include "interrupt/irq.h"
#include "../drivers/screen.h"
#include "../libc/string.h"

/* Declaration of Private Timer functions */
static void _timer_callback();

/****************************************************************
 * Public Timer functions                                       *
 ****************************************************************/

void init_timer(uint32_t frequency) {
    register_interrupt_handler(IRQ0, _timer_callback);

    const uint32_t divisor = HARDWARE_PIT_FREQ / frequency;
    const uint8_t low  = (uint8_t)(divisor & 0xFF),
        high = (uint8_t)((divisor >> 8) & 0xFF);

    port_byte_out(REG_PIT_CTRL, 0x36);  /* tell the PIT which channel we're setting */
    port_byte_out(REG_PIT_DATA_CHANNEL_0, low);  /* send low byte */
    port_byte_out(REG_PIT_DATA_CHANNEL_0, high);  /* send high byte */
}

/****************************************************************
 * Private Timer functions                                      *
 ****************************************************************/

static void _timer_callback() {
    ++tick;

    kprint_at_colored("Tick: ", 1, 66, 1, light_brown, black);
    kprint_at_colored(itoa(tick), 1, 73, 1, light_brown, black);
}
