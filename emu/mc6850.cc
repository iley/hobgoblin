#include "mc6850.h"

namespace {

const size_t BUFFER_SIZE = 1024;

const uint8_t CTRL_RECVIRQ = 0x80;

const uint8_t STATUS_RDRF = 0x01;
const uint8_t STATUS_TDRE = 0x02;
const uint8_t STATUS_CTS = 0x08;
const uint8_t STATUS_IRQ = 0x80;

} // namespace

namespace emu {

MC6850::MC6850()
    : input_channel_(BUFFER_SIZE)
    , output_channel_(BUFFER_SIZE)
{}

void MC6850::Write(uint16_t address, uint8_t value) {
    if (address == 0) { // Control
        SetControl(value);
    } else if (address == 1) { // Data
        output_channel_.Send(value);
    }
}

uint8_t MC6850::Read(uint16_t address) {
    if (address == 0) { // Status
        uint8_t control = Control();
        uint8_t status = STATUS_TDRE | STATUS_CTS;
        if (!input_channel_.Empty()) {
            status |= STATUS_RDRF;
            if (control & CTRL_RECVIRQ) {
                status |= STATUS_IRQ;
            }
        }
        return status;
    } else if (address == 1) { // Data
        auto value = input_channel_.TryReceive();
        if (!value) {
            return 0x00;
        }
        return *value;
    } else {
        return 0x00;
    }
}

bool MC6850::InterruptRequested() {
    return (Control() & CTRL_RECVIRQ) && !input_channel_.Empty();
}

void MC6850::Send(uint8_t value) {
    input_channel_.Send(value);
}

uint8_t MC6850::Receive() {
    return output_channel_.Receive();
}

void MC6850::SetControl(uint8_t value) {
    std::scoped_lock lock(mutex_);
    control_ = value;
}

uint8_t MC6850::Control() const {
    std::scoped_lock lock(mutex_);
    return control_;
}

} // namespace emu
