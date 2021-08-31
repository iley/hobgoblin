#include "device.h"

#include <cassert>

namespace emu {

Device::~Device() {}

void Device::WriteBlock(uint16_t address, std::vector<uint8_t> bytes) {
    assert(bytes.size() <= 0x10000);
    for (size_t i = 0; i < bytes.size(); i++) {
        Write(address + static_cast<uint16_t>(i), bytes[i]);
    }
}

} // namespace emu
