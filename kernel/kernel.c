#include "../drivers/screen.h"

void main() {
    clear_screen();

    // Fill up the screen
    uint8_t i = 0;
    for (i = 0; i < 24; i++) {
        char str[255];
        int_to_ascii(i, str);
        kprint_at(str, i, 0);
    }

    kprint_at("This text forces the kernel to scroll. Row 0 will disappear.\n", 24, 0);
    kprint("And with this text, the kernel will scroll again, and row 1 will disappear too!\n");
}
