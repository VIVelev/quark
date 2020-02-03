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
 * Set given value to memory cells.
 * 
 * @param destination pointer
 * @param val the given value
 * @param len integer, number of memory cells
 */
void memory_set(uint8_t *destination, uint8_t val, uint32_t len) {
    for (uint32_t i = 0; i < len; i++)
        destination[i] = val;
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
    reverse(str);
}

/**
 * Reverses a string - inplace.
 * 
 * @param str string
 */
void reverse(char str[]) {
    uint32_t i, j;
    char tmp;

    for (i = 0, j = strlen(str) - 1; i < j; i++, j--) {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
}

/**
 * Returns the len of a string.
 * 
 * @param str string
 */
uint32_t strlen(char str[]) {
    uint32_t i = 0;
    while (str[i] != '\0') i++;

    return i;
}
