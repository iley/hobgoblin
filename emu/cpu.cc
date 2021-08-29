#define CHIPS_IMPL
#include "cpu.h"

namespace emu {

namespace {

uint64_t tick_callback(int num_ticks, uint64_t pins, void* user_data) {
    Z80CPU* cpu = static_cast<Z80CPU*>(user_data);
    return cpu->TickCallback(num_ticks, pins);
}

} // namespace

Z80CPU::Z80CPU(Device* memory, Device* io)
    : memory_(memory)
    , io_(io) {
    z80_desc_t desc {
        .tick_cb = &tick_callback,
        .user_data = this,
    };
    z80_init(&z80_, &desc);
}

void Z80CPU::Reset() {
    z80_reset(&z80_);
}

uint32_t Z80CPU::Exec(uint32_t ticks) {
    return z80_exec(&z80_, ticks);
}

uint64_t Z80CPU::TickCallback(int /*num_ticks*/, uint64_t pins) {
    if (pins & Z80_MREQ) {
        if (pins & Z80_RD) {
            Z80_SET_DATA(pins, memory_->Read(Z80_GET_ADDR(pins)));
        } else if (pins & Z80_WR) {
            memory_->Write(Z80_GET_ADDR(pins), Z80_GET_DATA(pins));
        }
    } else if (pins & Z80_IORQ) {
        if (pins & Z80_RD) {
            Z80_SET_DATA(pins, io_->Read(Z80_GET_ADDR(pins)));
        } else if (pins & Z80_WR) {
            io_->Write(Z80_GET_ADDR(pins), Z80_GET_DATA(pins));
        }
    }
    return pins;
}

Z80Registers Z80CPU::Registers() {
    Z80Registers registers;
    registers.af = z80_af(&z80_);
    registers.bc = z80_bc(&z80_);
    registers.de = z80_de(&z80_);
    registers.hl = z80_hl(&z80_);
    registers.sp = z80_sp(&z80_);
    registers.pc = z80_pc(&z80_);
    registers.ix = z80_ix(&z80_);
    registers.iy = z80_iy(&z80_);
    registers.i = z80_i(&z80_);
    registers.r = z80_r(&z80_);
    return registers;
}

} // namespace emu
