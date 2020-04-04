#ifndef BITWISE_H
#define BITWISE_H

#include "../cpu/type.h"

#define low_16(address) (uint16_t)(address & 0xFFFF)
#define high_16(address) (uint16_t)((address >> 16) & 0xFFFF)

#endif /* BITWISE_H */
