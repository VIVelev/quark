#ifndef KEYBOARD_H
    #define KEYBOARD_H

    /* The PIC leaves us the scancode in port 0x60 */
    #define REG_SCANCODE_DATA 0x60

    #define BACKSPACE_SC 0x0e  /* Scancode for backspace */
    #define ENTER_SC 0x1c  /* Scancode for enter */
    #define MAX_SC 57

    char key_buffer[256];

    void init_keyboard();

#endif /* KEYBOARD_H */
