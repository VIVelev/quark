#ifndef UTILS_H
    #define UTILS_H

    #include "../cpu/types.h"

    #define low_16(address) (uint16_t)(address & 0xFFFF)
    #define high_16(address) (uint16_t)((address >> 16) & 0xFFFF)

    void memory_copy(uint8_t *source, uint8_t *destination, uint32_t nbytes);
    void int_to_ascii(sint32_t n, char str[]);

#endif /* UTILS_H */
