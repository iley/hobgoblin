#ifndef _HOBGOBLIN_EMU_MEMORY_H
#define _HOBGOBLIN_EMU_MEMORY_H

#include <cstdio>
#include <vector>

#include "device.h"

namespace emu {

class Memory : public Device {
public:
    enum class AccessMode {
        READONLY,
        READWRITE,
    };

    explicit Memory(const uint16_t size, AccessMode mode=AccessMode::READWRITE);

    void Write(uint16_t address, uint8_t value) override;
    uint8_t Read(uint16_t address) override;

    uint16_t Load(const std::vector<uint8_t> source, uint16_t offset=0);
    uint16_t Load(FILE* source, uint16_t offset=0);

private:
    std::vector<uint8_t> data_;
    AccessMode mode_;
};

} // namespace emu

#endif // _HOBGOBLIN_EMU_MEMORY_H 
