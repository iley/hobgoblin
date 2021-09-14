#include "mc6850.h"

namespace {

const size_t kBufferSize = 1024;

const uint8_t CTRL_RECVIRQ = 0x80;

const uint8_t STATUS_RDRF = 0x01;
const uint8_t STATUS_TDRE = 0x02;
const uint8_t STATUS_CTS = 0x08;
const uint8_t STATUS_IRQ = 0x80;

} // namespace

namespace emu {

MC6850::MC6850()
    : input_channel_(kBufferSize)
    , output_channel_(kBufferSize)
{}

void MC6850::Write(uint16_t address, uint8_t value) {
    printf("write(%x, %x)\n", address, value);
    if (address == 0) {
        SetControl(value);
    } else if (address == 1) {
        output_channel_.Send(value);
    }
}

uint8_t MC6850::Read(uint16_t address) {
    printf("read(%x)\n", address);
    if (address == 0) {
        uint8_t control = Control();
        uint8_t status = STATUS_TDRE | STATUS_CTS;
        if (!input_channel_.Empty()) {
            status |= STATUS_RDRF;
            if (control & CTRL_RECVIRQ) {
                status |= STATUS_IRQ;
            }
        }
        return status;
    } else if (address == 1) {
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
