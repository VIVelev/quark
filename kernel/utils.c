#include "utils.h"

/**
 * Copy nbytes from source into destination.
 * Simplified implementation of `memcpy`.
 * 
 * @param source pointer
 * @param destination pointer
 * @param nbytes integer, number of bytes
 */
void memory_copy(uint8_t *source, uint8_t *destination, uint32_t nbytes) {
    for (uint32_t i = 0; i < nbytes; i++)
        destination[i] = source[i];
}

/**
 * `itoa` implementation.
 * 
 * @param n integer
 * @param str string, destination
 */
void int_to_ascii(sint32_t n, char str[]) {
    sint32_t sign = n;
    if (sign < 0)
        n = -n;

    uint16_t i = 0;
    do {
        str[i++] = n % 10 + '0';
        n /= 10;
    } while (n > 0);

    if (sign < 0)
        str[i++] = '-';

    str[i] = '\0';
}
