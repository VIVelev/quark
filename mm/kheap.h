#ifndef KMM_H
#define KMM_H

#include "../cpu/type.h"

#define ZERO_LAST_12_BITS 0xFFFFF000
#define ALIGNMENT 0x1000 /* 4 KB aligned */

uint32_t placement_address = 0;

uint32_t kmalloc(uint32_t size, bool align, uint32_t *physical_address);

#endif /* KMM_H */
