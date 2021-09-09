#ifndef _HOBGOBLIN_EMU_BUS_H
#define _HOBGOBLIN_EMU_BUS_H

#include <exception>
#include <map>
#include <shared_mutex>
#include <optional>

#include "device.h"

namespace emu {

class Bus : public Device {
public:
    void Attach(Device* device, uint16_t start_address, uint16_t end_address);

    void Write(uint16_t address, uint8_t value) override;
    uint8_t Read(uint16_t address) override;

private:
    struct DeviceDescriptor {
        Device* device;
        uint16_t start_address;
        uint16_t end_address;
    };

    std::shared_mutex mutex_;
    std::map<uint16_t, DeviceDescriptor> device_map_;

    std::optional<DeviceDescriptor> FindDevice(uint16_t address);
};

} // namespace emu

#endif // _HOBGOBLIN_EMU_BUS_H
