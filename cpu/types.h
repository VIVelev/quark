#ifndef TYPES_H
    #define TYPES_H

    typedef unsigned char  uint8_t;
    typedef          char  sint8_t;
    typedef unsigned short uint16_t;
    typedef          short sint16_t;
    typedef unsigned int   uint32_t;
    typedef          int   sint32_t;

    #define low_16(address) (uint16_t)(address & 0xFFFF)
    #define high_16(address) (uint16_t)((address >> 16) & 0xFFFF)

#endif /* TYPES_H */
