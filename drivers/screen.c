#include "screen.h"
#include "ports.h"

// Declaration of Private Kernel functions
int print_char(char ch, int row, int col, char attr);
int get_cursor_offset();
void set_cursor_offset(int offset);
int get_cursor_offset_from(int row, int col);
int get_cursor_offset_row(int offset);
int get_cursor_offset_col(int offset);

/****************************************************************
 * Public Kernel functions                                      *
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
void kprint_at(char *message, int row, int col) {
    int offset, i = 0;
    while (message[i] != '\0') {
        offset = print_char(message[i++], row, col, WHITE_ON_BLACK);
        row = get_cursor_offset_row(offset);
        col  = get_cursor_offset_col(offset);
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
    kprint_at(message, -1, -1);
}

/**
 * Screen cleaning utility function.
 */
void clear_screen() {
    int i, screen_size = MAX_ROWS * MAX_COLS;
    unsigned char *vidmem = (unsigned char *) VIDEO_MEMORY_ADDRESS;

    for (i = 0; i < screen_size; i++) {
        vidmem[2*i] = ' ';
        vidmem[2*i + 1] = WHITE_ON_BLACK;
    }

    set_cursor_offset(get_cursor_offset_from(0, 0));
}

/****************************************************************
 * Private Kernel functions                                     *
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
int print_char(char ch, int row, int col, char attr) {
    unsigned char *vidmem = (unsigned char *) VIDEO_MEMORY_ADDRESS;
    if (!attr)
        attr = WHITE_ON_BLACK;

    // Print a red 'E' if the coords are out of bounds.
    if (row >= MAX_ROWS || col >= MAX_COLS) {
        vidmem[2 * MAX_ROWS*MAX_COLS - 2] = 'E';
        vidmem[2 * MAX_ROWS*MAX_COLS - 1] = RED_ON_WHITE;
        return get_cursor_offset_from(row, col);
    }

    int offset;
    if (row >= 0 && col >= 0)
        offset = get_cursor_offset_from(row, col);
    else
        offset = get_cursor_offset();

    if (ch == '\n') {
        row = get_cursor_offset_row(offset);
        offset = get_cursor_offset_from(row + 1, 0);

    }else {
        vidmem[offset] = ch;
        vidmem[offset+1] = attr;
        offset += 2;
    }

    set_cursor_offset(offset);
    return offset;
}

/**
 * Use the VGA ports to get the current cursor position.
 * 
 * 1. Ask for high byte of the cursor offset.
 * 2. Ask for low byte.
 */
int get_cursor_offset() {

    // 1. Ask for high byte of the cursor offset.
    port_byte_out(REG_SCREEN_CTRL, CURSOR_HIGH_BYTE_DATA);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;

    // 2. Ask for low byte.
    port_byte_out(REG_SCREEN_CTRL, CURSOR_LOW_BYTE_DATA);
    offset += port_byte_in(REG_SCREEN_DATA);

    // Since the cursor offset reported by the VGA hardware is the
    // number of characters, we multiply by two to convert it to
    // a character cell offset.
    return offset * 2;
}

/**
 * Similar to `get_cursor_offset`, but instead of reading we write data.
 * 
 * 1. Set high byte of the cursor offset.
 * 2. Set low byte.
 * 
 * @param offset
 */
void set_cursor_offset(int offset) {
    // Convert from cell offset to char offset.
    offset /= 2;

    // 1. Set high byte of the cursor offset.
    port_byte_out(REG_SCREEN_CTRL, CURSOR_HIGH_BYTE_DATA);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));

    // 2. Set low byte.
    port_byte_out(REG_SCREEN_CTRL, CURSOR_LOW_BYTE_DATA);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

int get_cursor_offset_from(int row, int col) {
    return 2 * (row * MAX_COLS + col);
}

int get_cursor_offset_row(int offset) {
    return offset / (2 * MAX_COLS);
}

int get_cursor_offset_col(int offset) {
    return (offset - 2 * MAX_COLS * get_cursor_offset_row(offset)) / 2;
}
