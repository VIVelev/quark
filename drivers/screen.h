#ifndef SCREEN_H
    #define SCREEN_H

    #include "../cpu/types.h"

    #define VIDEO_MEMORY_ADDRESS 0xb8000
    #define MAX_ROWS 25
    #define MAX_COLS 80
    #define WHITE_ON_BLACK 0x0f
    #define RED_ON_WHITE 0xf4

    /* Screen I/O Ports */
    #define REG_SCREEN_CTRL 0x3d4
    #define REG_SCREEN_DATA 0x3d5
    #define CURSOR_HIGH_BYTE_DATA 14
    #define CURSOR_LOW_BYTE_DATA 15

    #define BACKSPACE_ASCII 0x08  /* ASCII Code for backspace */

    /* Public Kernel functions */
    void kprint_at(char *message, uint32_t row, uint32_t col);
    void kprint(char *message);
    void kprint_backspace();
    void clear_screen();

#endif /* SCREEN_H */
