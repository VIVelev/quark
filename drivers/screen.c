#include "screen.h"
#include "../cpu/port.h"
#include "../libc/mem.h"

/* Declaration of Private Screen functions */
static uint32_t _print_char(char ch, uint32_t row, uint32_t col, vga_color_t fg, vga_color_t bg);
static uint32_t _get_cursor_offset();
static void _set_cursor_offset(uint32_t offset);
static uint32_t _get_cursor_offset_on(uint32_t row, uint32_t col);
static uint32_t _get_cursor_offset_row(uint32_t offset);
static uint32_t _get_cursor_offset_col(uint32_t offset);

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
 * @param retain_offset bool
 */ 
void kprint_at(const char *message, uint32_t row, uint32_t col, bool retain_offset) {
    const uint32_t saved_offset = _get_cursor_offset();
    uint32_t offset, i = 0;

    while (message[i] != '\0') {
        offset = _print_char(message[i++], row, col, light_grey, black);
        row = _get_cursor_offset_row(offset);
        col  = _get_cursor_offset_col(offset);
    }

    if (retain_offset)
        _set_cursor_offset(saved_offset);
}

/**
 * Colored Kernel Print at given screen position.
 * 
 * High-level print function.
 * 
 * @param message string to print
 * @param row integer
 * @param col integer
 * @param retain_offset bool
 * @param fg foreground color
 * @param bg background color
 */ 
void kprint_at_colored(const char *message, uint32_t row, uint32_t col, bool retain_offset,
                       vga_color_t fg, vga_color_t bg) {

    const uint32_t saved_offset = _get_cursor_offset();
    uint32_t offset, i = 0;

    while (message[i] != '\0') {
        offset = _print_char(message[i++], row, col, fg, bg);
        row = _get_cursor_offset_row(offset);
        col  = _get_cursor_offset_col(offset);
    }

    if (retain_offset)
        _set_cursor_offset(saved_offset);
}

/**
 * Kernel Print.
 * 
 * Prints a message on the screen at the current cursor position.
 * 
 * @param message string to print
 */
void kprint(const char *message) {
    uint32_t offset, row, col;
    offset = _get_cursor_offset();
    row = _get_cursor_offset_row(offset);
    col = _get_cursor_offset_col(offset);

    kprint_at(message, row, col, 0);
}

/**
 * Colored Kernel Print.
 * 
 * Prints a message on the screen at the current cursor position.
 * 
 * @param message string to print
 * @param fg foreground color
 * @param bg background color
 */
void kprint_colored(const char *message, vga_color_t fg, vga_color_t bg) {
    uint32_t offset, row, col;
    offset = _get_cursor_offset();
    row = _get_cursor_offset_row(offset);
    col = _get_cursor_offset_col(offset);

    kprint_at_colored(message, row, col, 0, fg, bg);
}

/**
 * Backspace.
 * Deletes the last character.
 */
void kprint_backspace() {
    uint32_t offset, row, col;
    offset = _get_cursor_offset() - 2;
    row = _get_cursor_offset_row(offset);
    col = _get_cursor_offset_col(offset);

    _print_char(BACKSPACE_ASCII, row, col, light_grey, black);
}

/**
 * Screen cleaning utility function.
 */
void clear_screen() {
    const uint32_t screen_size = NUM_ROWS * NUM_COLS;

    uint8_t *vidmem = (uint8_t *) VIDEO_MEMORY_ADDRESS;
    uint32_t i;

    for (i = 0; i < screen_size; i++) {
        vidmem[2*i] = ' ';
        vidmem[2*i + 1] = NEW_VGA_COLOR(light_grey, black);
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
 * @param fg foreground color
 * @param bg background color
 * 
 * @returns the offset of the next character
 */
static uint32_t _print_char(char ch, uint32_t row, uint32_t col, vga_color_t fg, vga_color_t bg) {
    uint8_t *vidmem = (uint8_t *) VIDEO_MEMORY_ADDRESS;

    /* Print a red 'E' if the coords are out of bounds. */
    if (row >= NUM_ROWS || col >= NUM_COLS) {
        vidmem[2 * NUM_ROWS*NUM_COLS - 2] = 'E';
        vidmem[2 * NUM_ROWS*NUM_COLS - 1] = NEW_VGA_COLOR(red, white);
        return _get_cursor_offset_on(row, col);
    }

    uint32_t offset = _get_cursor_offset_on(row, col);
    if (ch == '\n') {
        row = _get_cursor_offset_row(offset);
        offset = _get_cursor_offset_on(row + 1, 0);

    }else if (ch == BACKSPACE_ASCII) {
        vidmem[offset] = ' ';
        vidmem[offset + 1] = NEW_VGA_COLOR(fg, bg);

    }else {
        vidmem[offset] = ch;
        vidmem[offset + 1] = NEW_VGA_COLOR(fg, bg);
        offset += 2;
    }

    /* Check if the offset is over the screen size. If it is, then scroll. */
    if (offset >= 2 * NUM_ROWS * NUM_COLS) {
        uint32_t i;

        /* Scroll */
        for (i = 1; i < NUM_ROWS;  i++)
            memcpy(vidmem + _get_cursor_offset_on(i, 0),
                   vidmem + _get_cursor_offset_on(i-1, 0),
                   2 * NUM_COLS);

        /* The new, last line, is blank */
        uint8_t *last_line = vidmem + _get_cursor_offset_on(NUM_ROWS - 1, 0);
        for (i = 0; i < 2 * NUM_COLS; i++)
            last_line[i] = '\0';

        offset -= 2 * NUM_COLS;
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
static uint32_t _get_cursor_offset() {

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
static void _set_cursor_offset(uint32_t offset) {
    /* Convert from cell offset to char offset. */
    offset /= 2;

    /* 1. Set high byte of the cursor offset. */
    port_byte_out(REG_SCREEN_CTRL, CURSOR_HIGH_BYTE_DATA);
    port_byte_out(REG_SCREEN_DATA, (uint8_t)(offset >> 8));

    /* 2. Set low byte. */
    port_byte_out(REG_SCREEN_CTRL, CURSOR_LOW_BYTE_DATA);
    port_byte_out(REG_SCREEN_DATA, (uint8_t)(offset & 0xff));
}

static uint32_t _get_cursor_offset_on(uint32_t row, uint32_t col) {
    return 2 * (row * NUM_COLS + col);
}

static uint32_t _get_cursor_offset_row(uint32_t offset) {
    return offset / (2 * NUM_COLS);
}

static uint32_t _get_cursor_offset_col(uint32_t offset) {
    return (offset - 2 * NUM_COLS * _get_cursor_offset_row(offset)) / 2;
}
