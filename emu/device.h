#ifndef _HOBGOBLIN_EMU_DEVICE_H
#define _HOBGOBLIN_EMU_DEVICE_H

#include <cstdint>
#include <vector>

namespace emu {

class Device {
public:
    virtual ~Device();

    virtual void Write(uint16_t address, uint8_t value) = 0;
    virtual uint8_t Read(uint16_t address) = 0;

    void WriteBlock(uint16_t address, std::vector<uint8_t> bytes);
};

} // namespace emu

#endif // _HOBGOBLIN_EMU_DEVICE_H 
