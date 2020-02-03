#include "keyboard.h"
#include "screen.h"
#include "../cpu/irq.h"
#include "../cpu/ports.h"
#include "../libc/string.h"

/* Declaration of Private Keyboard functions */
static void _keyboard_callback();
static void _print_user_input();

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
        strpop(key_buffer);
        kprint_backspace();
        
    }else if (scancode == ENTER_SC) {
        kprint("\n");
        _print_user_input();
        key_buffer[0] = '\0';

    }else {
        char str[2] = {sc_ascii[(int) scancode], '\0'};
        strpush(key_buffer, str[0]);

        kprint(str);
    }
}

static void _print_user_input() {
    if (strcmp(key_buffer, "END") == 0) {
        kprint("Stopping the CPU. Bye!\n");
        __asm__("hlt");
    }

    kprint("You said: ");
    kprint(key_buffer);
    kprint("\n> ");
}
