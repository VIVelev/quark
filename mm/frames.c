#include "frames.h"
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
