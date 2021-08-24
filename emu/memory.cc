#include "memory.h"

namespace emu {

emu::RAM::RAM(const uint16_t size)
    : data_(static_cast<size_t>(size), 0x00)
{}

void emu::RAM::Write(uint16_t address, uint8_t value) {
    const auto index = static_cast<size_t>(address);
    if (index >= data_.size()) {
        // Out of bounds.
        return;
    }
    data_[index] = value;
}

uint8_t emu::RAM::Read(uint16_t address) {
    const auto index = static_cast<size_t>(address);
    if (index >= data_.size()) {
        // Out of bounds.
        return 0;
    }
    return data_[index];
}

} // namespace emu
