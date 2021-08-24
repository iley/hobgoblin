#ifndef _HOBGOBLIN_EMU_MEMORY_H
#define _HOBGOBLIN_EMU_MEMORY_H

#include <vector>

#include "device.h"

namespace emu {

class RAM : public Device {
public:
    explicit RAM(const uint16_t size);

    void Write(uint16_t address, uint8_t value) override;
    uint8_t Read(uint16_t address) override;

private:
    std::vector<uint8_t> data_;
};

} // namespace emu

#endif // _HOBGOBLIN_EMU_MEMORY_H 
