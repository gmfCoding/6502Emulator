#ifndef CML6502_PIN_H
#define CML6502_PIN_H
#include <ctypes.h>

union pin8_t
{
    uint8_t value;
    struct
    {
        uint8_t p0: 1;
        uint8_t p1: 1;
        uint8_t p2: 1;
        uint8_t p3: 1;
        uint8_t p4: 1;
        uint8_t p5: 1;
        uint8_t p6: 1;
        uint8_t p7: 1;
    } pins;
};

union pin16_t
{
    uint16_t value;
    struct
    {
        uint16_t p0: 1;
        uint16_t p1: 1;
        uint16_t p2: 1;
        uint16_t p3: 1;
        uint16_t p4: 1;
        uint16_t p5: 1;
        uint16_t p6: 1;
        uint16_t p7: 1;
        uint16_t p8: 1;
        uint16_t p9: 1;
        uint16_t pA: 1;
        uint16_t pB: 1;
        uint16_t pC: 1;
        uint16_t pD: 1;
        uint16_t pE: 1;
        uint16_t pF: 1;
    } pins;
};
#endif