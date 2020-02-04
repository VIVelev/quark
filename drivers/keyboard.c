#include "keyboard.h"
#include "screen.h"
#include "../cpu/ports.h"
#include "../cpu/interrupt/irq.h"
#include "../kernel/shell.h"
#include "../libc/string.h"

/* Declaration of Private Keyboard functions */
static void _keyboard_callback();

/****************************************************************
 * Public Keyboard functions                                    *
 ****************************************************************/

void init_keyboard() {
    register_interrupt_handler(IRQ1, _keyboard_callback); 
}

/****************************************************************
 * Private Keyboard functions                                   *
 ****************************************************************/

const char *sc_name[] = {
    "ERROR", "Esc",
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "Backspace",
    "Tab", "Q", "W", "E",  "R", "T", "Y", "U", "I", "O", "P", "[", "]",
    "Enter", "Lctrl",
    "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
    "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",  "/", "RShift",
    "Keypad *", "LAlt", "Spacebar"
};

const char sc_ascii[] = {
    '?', '?',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '?',
    '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']',
    '?', '?',
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`',
    '?', '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', '?',
    '?', '?', ' '
};

static void _keyboard_callback() {
    uint8_t scancode = port_byte_in(REG_SCANCODE_DATA);

    if (scancode > MAX_SC)
        return;

    if (scancode == BACKSPACE_SC) {
        kprint_backspace();
        strpop(key_buffer);

    }else if (scancode == ENTER_SC) {
        kprint("\n");
        evaluate(key_buffer);
        key_buffer[0] = '\0';

    }else {
        char str[2] = {sc_ascii[(int) scancode], '\0'};
        kprint(str);
        strpush(key_buffer, str[0]);
    }
}
