#include "frames.h"
#include "../drivers/screen.h"
#include "kheap.h"

/**
 * Sets the bit in the frames bitset
 * corresponding to the specified frame address.
 * 
 * @param frame_address
 * @return void
 */
void set_frame(uint32_t frame_address) {
    uint32_t frame = frame_address / ALIGNMENT;
    uint32_t index = INDEX(frame);
    uint32_t offset = OFFSET(frame);

    frames_bitset[index] |= (0x1 << offset);
}

/**
 * Clears the bit in the frames bitset
 * corresponding to the specified frame address.
 * 
 * @param frame_address
 * @return void
 */
void clear_frame(uint32_t frame_address) {
    uint32_t frame = frame_address / ALIGNMENT;
    uint32_t index = INDEX(frame);
    uint32_t offset = OFFSET(frame);

    frames_bitset[index] &= ~(0x1 << offset);
}

/**
 * Test if a frame (a bit in the frames bitset) is set
 * 
 * @param frame_address
 * @return 32-bit set, tested on the frame
 */
uint32_t test_frame(uint32_t frame_address) {
    uint32_t frame = frame_address / ALIGNMENT;
    uint32_t index = INDEX(frame);
    uint32_t offset = OFFSET(frame);

    return frames_bitset[index] & (0x1 << offset);
}

/**
 * Return the index of the first free frame
 * 
 */
uint32_t get_first_free_frame() {
    uint32_t index, offset, curr_frame;

    for (index = 0; index < INDEX(num_frames); ++index) {

        /* Check if anything is free */
        if (frames_bitset[index] != 0xFFFFFFFF) {
            /* At least on bit is free */

            for (offset = 0; offset < WORD_SIZE; ++offset) {
                curr_frame = index * WORD_SIZE + offset;

                /* Check if free */
                if (!test_frame(curr_frame * ALIGNMENT)) {
                    return curr_frame;
                }
            }
        }
    }

    return (uint32_t)-1;
}

void alloc_frame(page_t *page, bool is_kernel, bool is_writeable) {
    if (page->frame) {
        /* Frame already allocated */
        return;

    } else {
        uint32_t frame = get_first_free_frame();
        if (frame == (uint32_t)-1) {
            kprint("No free frame!\n");
        }

        set_frame(frame * ALIGNMENT);
        page->present = 1;
        page->rw = is_writeable ? 1 : 0;
        page->user = is_kernel ? 0 : 1;
        page->frame = frame;
    }
}

void free_frame(page_t *page) {
    uint32_t frame;

    if (!(frame = page->frame)) {
        /* The page doesn't have a frame */
        return;
    } else {
        clear_frame(frame * ALIGNMENT);
        page->frame = 0x0;
    }
}
