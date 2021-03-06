#include "kheap.h"

uint32_t kmalloc(uint32_t size, bool align, uint32_t *physical_address) {

    /* If we have to align the address and it is not aligned */
    if (align && (placement_address & ZERO_LAST_12_BITS)) {
        /* Align it */
        placement_address &= ZERO_LAST_12_BITS;
        placement_address += ALIGNMENT;
    }

    /* Get the physical_address of the memory allocated */
    if (physical_address) {
        *physical_address = placement_address;
    }

    uint32_t free_p = placement_address;
    placement_address += size;
    return free_p;
}
