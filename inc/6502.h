#ifndef CMLE6502_6502_H
#define CMLE6502_6502_H
#include <stdint.h>
#include <stdbool.h>

typedef int error_t;

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

enum icUID
{
    ICUID_6502
};

struct processor
{
    enum icUID ic_uid;
};


struct processor6502
{
    struct processor base;
    struct processor6502cpu
    {
        // Main register / Accumulator
        uint8_t a;
        union
        {
            uint8_t value;
            struct
            {
                // Negative
                uint8_t n: 1;
                // Overflow
                uint8_t v: 1;
                // Break
                uint8_t b: 1;
                // Decimal
                uint8_t d: 1;
                // Interupt disable
                uint8_t i: 1;
                // Zero
                uint8_t z: 1;
                // Carry
                uint8_t c: 1;
            };
        } flags;
       

        // Program counter
        uint16_t pc;
        // Stack pointer
        uint8_t S;
        // index register
        uint8_t X;
        // index register
        uint8_t Y;
    } cpu;

    uint8_t* memory;

    struct
    {
        union pin16_t addr;
        union pin8_t  data;
        bool    vcc;
    } pins;

    struct processor6502metadata
    {
        uint64_t cycles;
        uint64_t reads;
        uint64_t writes;
    } metadata;
};

error_t ic_power_on(struct processor* procbase);
error_t ic6502_power_on(struct processor6502* proc);
error_t ic6502_power_off(struct processor6502* proc);
error_t ic6502_restart(struct processor6502* proc);

error_t ic6502_cpu_flags_clear(struct processor6502* proc);
error_t ic6502_cpu_step(struct processor6502* proc);

error_t ic6502_memory_read(struct processor6502* proc, uint16_t addr, uint8_t* value);
error_t ic6502_memory_write(struct processor6502* proc, uint16_t addr, uint8_t value);
#endif