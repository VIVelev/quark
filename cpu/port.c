#include "port.h"

/**
 * Read a byte from the specified port.
 * 
 * @param port the specified port
 */
uint8_t port_byte_in(uint16_t port) {
    /**
     * "=a" ( result ) means : put AL register in variable RESULT when finished
     * "d" ( port ) means : load EDX with port
     */
    uint8_t result;
    __asm__("in %%dx, %%al"
            : "=a"(result)
            : "d"(port));
    return result;
}

/**
 * Write a byte to the specified port.
 * 
 * @param port the specified port
 * @param data the byte to write
 */
void port_byte_out(uint16_t port, uint8_t data) {
    /**
     * "a" ( data ) means : load EAX with data
     * "d" ( port ) means : load EDX with port
     */
    __asm__("out %%al, %%dx"
            :
            : "a"(data), "d"(port));
}

/**
 * Read a word from the specified port.
 * 
 * @param port the specified port
 */
uint16_t port_word_in(uint16_t port) {
    uint16_t result;
    __asm__("in %%dx, %%ax"
            : "=a"(result)
            : "d"(port));

    return result;
}

/**
 * Write a word to the specified port.
 * 
 * @param port the specified port
 * @param data the word to write
 */
void port_word_out(uint16_t port, uint16_t data) {
    __asm__("out %%ax, %%dx"
            :
            : "a"(data), "d"(port));
}
