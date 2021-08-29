#ifndef _HOBGOBLIN_EMU_CPU_H
#define _HOBGOBLIN_EMU_CPU_H

#include <cstdint>

#include "vendor/z80.h"

#include "device.h"

namespace emu {

class Z80CPU {
public:
    Z80CPU();
    void Reset();
    void Exec(uint32_t ticks);

    uint64_t TickCallback(int num_ticks, uint64_t pins);

private:
    z80_t z80_;
    Device* memory_;
    Device* io_;
};

} // namespace emu

#endif // _HOBGOBLIN_EMU_CPU_H 
