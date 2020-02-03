#ifndef STRING_H
    #define STRING_H

    #include "../cpu/types.h"

    char * itoa(sint32_t n);

    char * strrev(char *str);
    char * strpush(char *str, char c);
    char * strpop(char *str);

    uint32_t strlen(char *str);
    sint32_t strcmp(char *str1, char *str2);

#endif /* STRING_H */
