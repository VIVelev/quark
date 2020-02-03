#include "screen.h"
#include "../cpu/ports.h"
#include "../libc/mem.h"

/* Declaration of Private Screen functions */
uint32_t _print_char(char ch, uint32_t row, uint32_t col, uint8_t attr);
uint32_t _get_cursor_offset();
void _set_cursor_offset(uint32_t offset);
uint32_t _get_cursor_offset_on(uint32_t row, uint32_t col);
uint32_t _get_cursor_offset_row(uint32_t offset);
uint32_t _get_cursor_offset_col(uint32_t offset);

/****************************************************************
 * Public Screen functions                                      *
 ****************************************************************/

/**
 * Kernel Print at given screen position.
 * 
 * High-level print function.
 * 
 * @param message string to print
 * @param row integer
 * @param col integer
 */ 
void kprint_at(char *message, uint32_t row, uint32_t col) {
    uint32_t offset, i = 0;
    while (message[i] != '\0') {
        offset = _print_char(message[i++], row, col, WHITE_ON_BLACK);
        row = _get_cursor_offset_row(offset);
        col  = _get_cursor_offset_col(offset);
    }
}

/**
 * Kernel Print.
 * 
 * Prints a message on the screen at the current cursor position.
 * 
 * @param message string to print
 */
void kprint(char *message) {
    uint32_t offset, row, col;
    offset = _get_cursor_offset();
    row = _get_cursor_offset_row(offset);
    col = _get_cursor_offset_col(offset);

    kprint_at(message, row, col);
}

/**
 * Screen cleaning utility function.
 */
void clear_screen() {
    uint32_t i, screen_size = MAX_ROWS * MAX_COLS;
    uint8_t *vidmem = (uint8_t *) VIDEO_MEMORY_ADDRESS;

    for (i = 0; i < screen_size; i++) {
        vidmem[2*i] = ' ';
        vidmem[2*i + 1] = WHITE_ON_BLACK;
    }

    _set_cursor_offset(_get_cursor_offset_on(0, 0));
}

/****************************************************************
 * Private Screen functions                                     *
 ****************************************************************/

/**
 * Innermost low-level print function used by the kernel,
 * directly accesses the video memory.
 * 
 * @param ch character to print
 * @param row row-wise offset
 * @param col col-wise offset
 * @param attr character attribute
 * 
 * @returns the offset of the next character
 */
uint32_t _print_char(char ch, uint32_t row, uint32_t col, uint8_t attr) {
    uint8_t *vidmem = (uint8_t *) VIDEO_MEMORY_ADDRESS;
    if (!attr)
        attr = WHITE_ON_BLACK;

    /* Print a red 'E' if the coords are out of bounds. */
    if (row >= MAX_ROWS || col >= MAX_COLS) {
        vidmem[2 * MAX_ROWS*MAX_COLS - 2] = 'E';
        vidmem[2 * MAX_ROWS*MAX_COLS - 1] = RED_ON_WHITE;
        return _get_cursor_offset_on(row, col);
    }

    uint32_t offset = _get_cursor_offset_on(row, col);
    if (ch == '\n') {
        row = _get_cursor_offset_row(offset);
        offset = _get_cursor_offset_on(row + 1, 0);

    }else {
        vidmem[offset] = ch;
        vidmem[offset+1] = attr;
        offset += 2;
    }

    /* Check if the offset is over the screen size. If it is, then scroll. */
    if (offset >= 2 * MAX_ROWS * MAX_COLS) {
        uint32_t i;

        /* Scroll */
        for (i = 1; i < MAX_ROWS;  i++)
            memcpy(vidmem + _get_cursor_offset_on(i, 0),
                   vidmem + _get_cursor_offset_on(i-1, 0),
                   2 * MAX_COLS);

        /* The new, last line, is blank */
        uint8_t *last_line = vidmem + _get_cursor_offset_on(MAX_ROWS - 1, 0);
        for (i = 0; i < 2 * MAX_COLS; i++)
            last_line[i] = '\0';

        offset -= 2 * MAX_COLS;
    }

    _set_cursor_offset(offset);
    return offset;
}

/**
 * Use the VGA ports to get the current cursor position.
 * 
 * 1. Ask for high byte of the cursor offset.
 * 2. Ask for low byte.
 */
uint32_t _get_cursor_offset() {

    /* 1. Ask for high byte of the cursor offset. */
    port_byte_out(REG_SCREEN_CTRL, CURSOR_HIGH_BYTE_DATA);
    uint32_t offset = port_byte_in(REG_SCREEN_DATA) << 8;

    /* 2. Ask for low byte. */
    port_byte_out(REG_SCREEN_CTRL, CURSOR_LOW_BYTE_DATA);
    offset += port_byte_in(REG_SCREEN_DATA);

    /**
     * Since the cursor offset reported by the VGA hardware is the
     * number of characters, we multiply by two to convert it to
     * a character cell offset.
     */
    return offset * 2;
}

/**
 * Similar to `_get_cursor_offset`, but instead of reading we write data.
 * 
 * 1. Set high byte of the cursor offset.
 * 2. Set low byte.
 * 
 * @param offset
 */
void _set_cursor_offset(uint32_t offset) {
    /* Convert from cell offset to char offset. */
    offset /= 2;

    /* 1. Set high byte of the cursor offset. */
    port_byte_out(REG_SCREEN_CTRL, CURSOR_HIGH_BYTE_DATA);
    port_byte_out(REG_SCREEN_DATA, (uint8_t)(offset >> 8));

    /* 2. Set low byte. */
    port_byte_out(REG_SCREEN_CTRL, CURSOR_LOW_BYTE_DATA);
    port_byte_out(REG_SCREEN_DATA, (uint8_t)(offset & 0xff));
}

uint32_t _get_cursor_offset_on(uint32_t row, uint32_t col) {
    return 2 * (row * MAX_COLS + col);
}

uint32_t _get_cursor_offset_row(uint32_t offset) {
    return offset / (2 * MAX_COLS);
}

uint32_t _get_cursor_offset_col(uint32_t offset) {
    return (offset - 2 * MAX_COLS * _get_cursor_offset_row(offset)) / 2;
}
