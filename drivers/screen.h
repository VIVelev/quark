#ifndef SCREEN_H
    #define SCREEN_H

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

    /* Public Kernel functions */
    void kprint_at(char *message, int row, int col);
    void kprint(char *message);
    void clear_screen();

#endif /* SCREEN_H */