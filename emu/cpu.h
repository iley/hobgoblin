#ifndef _HOBGOBLIN_EMU_CPU_H
#define _HOBGOBLIN_EMU_CPU_H

#include <cstdint>

#include "vendor/z80.h"

#include "device.h"

namespace emu {

struct Z80Registers {
    uint16_t af;
    uint16_t bc;
    uint16_t de;
    uint16_t hl;

    uint16_t sp;
    uint16_t pc;

    uint16_t ix;
    uint16_t iy;

    uint8_t i;
    uint8_t r;
};

class Z80CPU {
public:
    Z80CPU(Device* memory, Device* io);
    void Reset();
    uint32_t Exec(uint32_t ticks);  // Returns number of executed ticks.

    uint64_t TickCallback(int num_ticks, uint64_t pins);

    Z80Registers Registers();

private:
    z80_t z80_;
    Device* memory_;
    Device* io_;
};

} // namespace emu

#endif // _HOBGOBLIN_EMU_CPU_H 
