#include "string.h"

/**
 * Integer to Ascii conversion.
 * 
 * @param n integer
 */
char *itoa(sint32_t n) {
    static char str[256];

    const sint32_t sign = n;
    if (sign < 0)
        n = -n;

    register uint16_t i = -1;
    do {
        str[++i] = n % 10 + '0';
        n /= 10;
    } while (n > 0);

    if (sign < 0)
        str[++i] = '-';

    str[++i] = '\0';
    return strrev(str);
}

/**
 * Reverses a string - inplace.
 * 
 * @param str string
 */
char *strrev(char *str) {
    register uint32_t i, j;
    char tmp;

    for (i = 0, j = strlen(str) - 1; i < j; ++i, --j) {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }

    return str;
}

/**
 * Append a character to the end of a string.
 * 
 * @param str string
 * @param c character to append
 */
char *strpush(char *str, char c) {
    const uint32_t len = strlen(str);
    str[len] = c;
    str[len + 1] = '\0';

    return str;
}

/**
 * Deletes the last character of a string.
 * 
 * @param str string
 */
char *strpop(char *str) {
    str[strlen(str) - 1] = '\0';
    return str;
}

/**
 * Returns the len of a string.
 * 
 * @param str string
 */
uint32_t strlen(const char *str) {
    register uint32_t i = 0;
    while (str[i] != '\0')
        ++i;

    return i;
}

/**
 * K&R strcmp 
 * Returns:
 *   < 0 if str1 < str2
 *   = 0 if str1 == str2
 *   > 0 if str1 > str2
 * 
 * @param str1 string
 * @param str2 string
 */
sint32_t strcmp(const char *str1, const char *str2) {
    register uint32_t i;
    for (i = 0; str1[i] == str2[i]; ++i) {
        if (str1[i] == '\0')
            return 0;
    }

    return str1[i] - str2[i];
}

/**
 * Implementation of djb2 hash function.
 * Reference: http://www.cse.yorku.ca/~oz/hash.html
 * 
 * @param str string to hash
 * @param limit integer, the maximum hash value
 */
uint32_t strhash(const char *str, uint32_t limit) {
    register uint32_t hash = 5381;
    register char c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % limit;
}
