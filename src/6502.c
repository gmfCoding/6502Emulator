#include "6502.h"

error_t ic6502_power_on(struct processor6502* proc)
{
    if (proc->pins.vcc == true)
        return ERR_OK
    proc->cpu = {0};
    proc->pins.vcc = true;

}

error_t ic6502_power_off(struct processor6502* proc)
{

}

error_t ic6502_restart(struct processor6502* proc);

error_t ic6502_cpu_flags_clear(struct processor6502* proc);
error_t ic6502_cpu_step(struct processor6502* proc);

error_t ic6502_memory_read(struct processor6502* proc, uint16_t addr, uint8_t* value);
error_t ic6502_memory_write(struct processor6502* proc, uint16_t addr, uint8_t value);