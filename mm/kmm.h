#ifndef KMM_H
#define KMM_H

#include <stdint.h>
#include "../cpu/type.h"

#define ZERO_LAST_12 0xFFFFF000
#define FOUR_KB 0x1000

uint32_t placement_address = 0;

uint32_t kmalloc(uint32_t size, bool align, uint32_t *physical_address);

#endif /* KMM_H */
