#ifndef COLOR_H
#define COLOR_H

#include "../cpu/type.h"

#define NEW_VGA_COLOR(fg, bg) ((uint8_t)(bg) << 4) | ((uint8_t)(fg))

typedef enum {
    black = 0,
    vlue = 1,
    green = 2,
    cyan = 3,
    red = 4,
    magneta = 5,
    brown = 6,
    light_grey = 7,
    dark_grey = 8,
    light_blue = 9,
    light_green = 10,
    light_cyan = 11,
    light_red = 12,
    light_magneta = 13,
    light_brown = 14,
    white = 15
} vga_color_t;

#endif /* COLOR_H */
