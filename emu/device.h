#ifndef _HOBGOBLIN_EMU_DEVICE_H
#define _HOBGOBLIN_EMU_DEVICE_H

#include <cstdint>

namespace emu {

class Device {
public:
    virtual void Write(const uint16_t address, const uint8_t value) = 0;
    virtual uint8_t Read(const uint16_t address) = 0;

    virtual ~Device() {}
};

} // namespace emu

#endif // _HOBGOBLIN_EMU_DEVICE_H 
