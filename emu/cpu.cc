#include "cpu.h"

#define CHIPS_IMPL
#include "vendor/z80.h"

namespace emu {

namespace {

uint64_t tick_callback(int num_ticks, uint64_t pins, void* user_data) {
    Z80CPU* cpu = static_cast<Z80CPU*>(user_data);
    return cpu->TickCallback(num_ticks, pins);
}

} // namespace

Z80CPU::Z80CPU() {
    z80_desc_t desc {
        .tick_cb = &tick_callback,
        .user_data = this,
    };
    z80_init(&z80_, &desc);
}

void Z80CPU::Reset() {
}

uint64_t Z80CPU::TickCallback(int num_ticks, uint64_t pins) {
    if (pins & Z80_MREQ) {
        if (pins & Z80_RD) {
            Z80_SET_DATA(pins, mem[Z80_GET_ADDR(pins)]);
        }
        else if (pins & Z80_WR) {
            mem[Z80_GET_ADDR(pins)] = Z80_GET_DATA(pins);
        }
    }
    else if (pins & Z80_IORQ) {
        // FIXME: perform device I/O
    }
    return pins;
}

} // namespace emu
