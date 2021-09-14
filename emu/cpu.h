#ifndef _HOBGOBLIN_EMU_CPU_H
#define _HOBGOBLIN_EMU_CPU_H

#include <cstdint>
#include <vector>

#include "third_party/z80.h"

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

    uint8_t a() const { return hi(af); }
    uint8_t f() const { return lo(af); }
    uint8_t b() const { return hi(bc); }
    uint8_t c() const { return lo(bc); }
    uint8_t d() const { return hi(de); }
    uint8_t e() const { return lo(de); }
    uint8_t h() const { return hi(hl); }
    uint8_t l() const { return lo(hl); }

private:
    static uint8_t hi(uint16_t val) { return (val >> 8) & 0xff; }
    static uint8_t lo(uint16_t val) { return val & 0xff; }
};

class Z80CPU {
public:
    Z80CPU(Device* memory, Device* io);
    void Reset();
    uint32_t Exec(uint32_t ticks);  // Returns number of executed ticks.
    void AddInterruptSource(InterruptSource* source);

    uint64_t TickCallback(int num_ticks, uint64_t pins);

    Z80Registers Registers();

private:
    z80_t z80_;
    Device* memory_;
    Device* io_;
    std::vector<InterruptSource*> interrupt_sources_;
};

} // namespace emu

#endif // _HOBGOBLIN_EMU_CPU_H 
