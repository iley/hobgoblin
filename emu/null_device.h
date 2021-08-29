#ifndef _HOBGOBLIN_EMU_NULLDEVICE_H
#define _HOBGOBLIN_EMU_NULLDEVICE_H

#include "device.h"

namespace emu {

class NullDevice : public Device {
public:
    void Write(uint16_t address, uint8_t value) override;
    uint8_t Read(uint16_t address) override;
};

} // namespace emu

#endif // _HOBGOBLIN_EMU_NULLDEVICE_H
