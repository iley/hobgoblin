#include "memory.h"

#include <cstring>

namespace emu {

Memory::Memory(size_t size, Memory::AccessMode mode)
    : data_(size, 0x00)
    , mode_(mode)
{}

void Memory::Write(uint16_t address, uint8_t value) {
    if (mode_ != AccessMode::READWRITE) {
        return;
    }
    if (address >= data_.size()) {
        return; // Out of bounds.
    }
    data_[address] = value;
}

uint8_t Memory::Read(uint16_t address) {
    if (address >= data_.size()) {
        return 0; // Out of bounds.
    }
    return data_[address];
}

uint16_t Memory::Load(const std::vector<uint8_t> source, uint16_t offset) {
    const size_t length = std::min(data_.size() - offset, source.size());
    std::memcpy(data_.data() + offset, source.data(), length);
    return static_cast<uint16_t>(length);
}

uint16_t Memory::Load(FILE* source, uint16_t offset) {
    uint16_t address = offset;
    int ch;
    while ((ch = std::fgetc(source)) != EOF && address < data_.size()) {
        data_[address] = static_cast<uint8_t>(ch);
        address++;
    }
    return address - offset;
}

} // namespace emu
