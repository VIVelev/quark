#ifndef KEYBOARD_H
    #define KEYBOARD_H

    /* The PIC leaves us the scancode in port 0x60 */
    #define REG_SCANCODE_DATA 0x60

    void init_keyboard();

#endif /* KEYBOARD_H */
