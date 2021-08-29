#include "bus.h"

#include <algorithm>
#include <cassert>

using std::nullopt;

namespace emu {

void Bus::Attach(Device* device, uint16_t start_address, uint16_t end_address) {
    // Verify that new mapping does not overlap with any of the existing ones.
    // Overlapping mappings are not supported.
    assert(std::all_of(device_map_.cbegin(), device_map_.cend(), [&start_address, &end_address](const auto& pair) {
        return end_address < pair.second.start_address || start_address > pair.second.end_address;
    }));
    device_map_[start_address] = DeviceDescriptor{
        .device = device,
        .start_address = start_address,
        .end_address = end_address,
    };
}

void Bus::Write(const uint16_t address, const uint8_t value) {
    auto desc = FindDevice(address);
    if (!desc) {
        return;
    }
    desc->device->Write(address - desc->start_address, value);
}

uint8_t Bus::Read(const uint16_t address) {
    auto desc = FindDevice(address);
    if (!desc) {
        return 0;
    }
    return desc->device->Read(address - desc->start_address);
}

std::optional<Bus::DeviceDescriptor> Bus::FindDevice(uint16_t address) {
    if (device_map_.empty()) {
        return nullopt;
    }
    auto it = device_map_.lower_bound(address);
    if (it != device_map_.begin() && it->first != address) {
        it--;
    }
    const auto& desc = it->second;
    if (address < desc.start_address || address > desc.end_address) {
        return nullopt;
    }
    return desc;
}

} // namespace emu
