#include "6502.h"
#include "extra.h"
#include "coreutil.h"

error_t ic6502_power_on(struct processor6502* proc)
{
    if (proc->pins.vcc == true)
        return ERR_OK;
    proc->cpu = (struct processor6502cpu){0};
    proc->pins.vcc = true;
    return ERR_OK;
}

error_t ic6502_power_off(UNUSED struct processor6502* proc)
{
    return ERR_OK;
}

error_t ic6502_restart(struct processor6502* proc)
{
    error_t prop = ERR_OK;
    prop = ic6502_power_off(proc);
    ERROR_CHECK(prop)
    prop = ic6502_cpu_flags_clear(proc);
    ERROR_CHECK(prop)
    prop = ic6502_power_on(proc);
    ERROR_CHECK(prop)
    return ERR_OK;
}

error_t ic6502_cpu_flags_clear(struct processor6502* proc)
{
    proc->cpu.flags.value = 0;
    return ERR_OK;
}

error_t ic6502_cpu_step(UNUSED struct processor6502* proc)
{
    return ERR_OK;
}

error_t ic6502_memory_read(UNUSED struct processor6502* proc, UNUSED uint16_t addr, UNUSED uint8_t* value)
{
    return ERR_OK;
}

error_t ic6502_memory_write(UNUSED struct processor6502* proc, UNUSED uint16_t addr, UNUSED uint8_t value)
{
    return ERR_OK;
}