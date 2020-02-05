#ifndef SCREEN_H
    #define SCREEN_H

    #include "color.h"

    #define VIDEO_MEMORY_ADDRESS 0xb8000
    #define NUM_ROWS 25
    #define NUM_COLS 80

    /* Screen I/O port */
    #define REG_SCREEN_CTRL 0x3d4
    #define REG_SCREEN_DATA 0x3d5
    #define CURSOR_HIGH_BYTE_DATA 14
    #define CURSOR_LOW_BYTE_DATA 15

    #define BACKSPACE_ASCII 0x08  /* ASCII Code for backspace */

    /* Public Kernel functions */
    void kprint_at(const char *message, uint32_t row, uint32_t col, bool save_offset);
    void kprint_at_colored(const char *message, uint32_t row, uint32_t col, bool save_offset,
                           vga_color_t fg, vga_color_t bg);

    void kprint(const char *message);
    void kprint_colored(const char *message,
                        vga_color_t fg, vga_color_t bg);

    void kprint_backspace();
    void clear_screen();

#endif /* SCREEN_H */
