#include "string.h"

/**
 * Integer to Ascii conversion.
 * 
 * @param n integer
 */
char * itoa(sint32_t n) {
    char str[256];

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
    return strrev(str);
}

/**
 * Reverses a string - inplace.
 * 
 * @param str string
 */
char * strrev(char *str) {
    uint32_t i, j;
    char tmp;

    for (i = 0, j = strlen(str) - 1; i < j; i++, j--) {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }

    return str;
}

/**
 * Returns the len of a string.
 * 
 * @param str string
 */
uint32_t strlen(char *str) {
    uint32_t i = 0;
    while (str[i] != '\0') i++;

    return i;
}