#ifndef UTILS_H
    #define UTILS_H

    #include "../cpu/types.h"

    #define low_16(address) (uint16_t)(address & 0xFFFF)
    #define high_16(address) (uint16_t)((address >> 16) & 0xFFFF)

    void memory_copy(uint8_t *source, uint8_t *destination, uint32_t nbytes);
    void memory_set(uint8_t *destination, uint8_t val, uint32_t len);

    void int_to_ascii(sint32_t n, char str[]);
    void reverse(char str[]);
    uint32_t strlen(char str[]);

#endif /* UTILS_H */
