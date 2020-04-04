#ifndef FRAMES_H
#define FRAMES_H

#include "../cpu/type.h"
#include "paging.h"

#define INDEX(frame) (frame / WORD_SIZE)
#define OFFSET(frame) (frame % WORD_SIZE)

uint32_t *frames_bitset;
uint32_t num_frames;

/* defined in kheap.h */
extern uint32_t placement_address;

/* Bits set actions */
void set_frame(uint32_t frame_address);
void clear_frame(uint32_t frame_address);
uint32_t test_frame(uint32_t frame_address);

/* Frames management functions */
uint32_t get_first_free_frame();
void alloc_frame(page_t *page, bool is_kernel, bool is_writeable);
void free_frame(page_t *page);

#endif /* FRAMES_H */
