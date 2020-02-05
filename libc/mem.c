#include "mem.h"

/**
 * Copy nbytes from source into destination.
 * 
 * @param src pointer
 * @param dest pointer
 * @param nbytes integer, number of bytes to copy
 */
void memcpy(const uint8_t *src, uint8_t *dest, uint32_t nbytes) {
    for (uint32_t i = 0; i < nbytes; i++)
        dest[i] = src[i];
}

/**
 * Set given value to memory cells.
 * 
 * @param dest pointer
 * @param val the given value
 * @param nbytes integer, number of memory cells
 */
void memset(uint8_t *dest, uint8_t val, uint32_t nbytes) {
    for (uint32_t i = 0; i < nbytes; i++)
        dest[i] = val;
}
