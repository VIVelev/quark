#ifndef MEM_H
#define MEM_H

#include "../cpu/type.h"

void memcpy(const uint8_t *src, uint8_t *dest, uint32_t nbytes);
void memset(uint8_t *dest, uint8_t val, uint32_t nbytes);

#endif /* MEM_H */
