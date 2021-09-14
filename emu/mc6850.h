#ifndef _HOBGOBLIN_EMU_MC6850_H
#define _HOBGOBLIN_EMU_MC6850_H

#include <mutex>

#include "channel.h"
#include "device.h"

namespace emu {

class MC6850 : public Device {
public:
    MC6850();

    void Write(uint16_t address, uint8_t value) override;
    uint8_t Read(uint16_t address) override;
    bool InterruptRequested() override;

    void Send(uint8_t value); // Blocks when input buffer is full.
    uint8_t Receive(); // Blocks when output buffer is empty.

private:
    mutable std::mutex mutex_;
    uint8_t control_;
    Channel<uint8_t> input_channel_;
    Channel<uint8_t> output_channel_;

    void SetControl(uint8_t value);
    uint8_t Control() const;
};

} // namespace emu

#endif // _HOBGOBLIN_EMU_MC6850_H 
