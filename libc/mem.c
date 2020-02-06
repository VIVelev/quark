#include "mem.h"

/**
 * Copy nbytes from source into destination.
 * 
 * @param src pointer
 * @param dest pointer
 * @param nbytes integer, number of bytes to copy
 */
void memcpy(const uint8_t *src, uint8_t *dest, uint32_t nbytes) {
    register const uint8_t *src_ptr;
    register uint8_t *dest_ptr;

    for (src_ptr = src, dest_ptr = dest; src_ptr < src + nbytes; ++src_ptr, ++dest_ptr)
        *dest_ptr = *src_ptr;
}

/**
 * Set given value to memory cells.
 * 
 * @param dest pointer
 * @param val the given value
 * @param nbytes integer, number of memory cells
 */
void memset(uint8_t *dest, uint8_t val, uint32_t nbytes) {
    register uint8_t *ptr;
    for (ptr = dest; ptr < dest + nbytes; ++ptr)
            *ptr = val;
}
