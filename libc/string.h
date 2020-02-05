#ifndef STRING_H
    #define STRING_H

    #include "../cpu/type.h"

    char * itoa(sint32_t n);

    char * strrev(char *str);
    char * strpush(char *str, char c);
    char * strpop(char *str);

    uint32_t strlen(const char *str);
    sint32_t strcmp(const char *str1, const char *str2);

#endif /* STRING_H */
