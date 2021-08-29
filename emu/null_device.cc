#include "null_device.h"

namespace emu {

void NullDevice::Write(uint16_t /*address*/, uint8_t /*value*/) {
    // do nothing
}

uint8_t NullDevice::Read(uint16_t /*address*/) {
    return 0;
}

} // namespace emu
