#include "utils.h"

/**
 * Copy nbytes from source into destination.
 * Simplified implementation of `memcpy`.
 * 
 * @param source pointer
 * @param destination pointer
 * @param nbytes integer, number of bytes
 */
void memory_copy(unsigned char *source, unsigned char *destination, unsigned int nbytes) {
    for (int i = 0; i < nbytes; i++)
        destination[i] = source[i];
}

/**
 * `itoa` implementation.
 * 
 * @param n integer
 * @param str string, destination
 */
void int_to_ascii(int n, char str[]) {
    int i = 0, sign = n;

    if (sign < 0)
        n = -n;

    do {
        str[i++] = n % 10 + '0';
        n /= 10;
    } while (n > 0);

    if (sign < 0)
        str[i++] = '-';

    str[i] = '\0';
}
