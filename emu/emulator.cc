#include "emulator.h"

const uint32_t kTicks = 1000;

namespace emu {

void Emulator::RunBackground() {
    std::thread thread([this] { this->Run(); });
    thread_ = std::move(thread);
}

void Emulator::Run() {
    while (!stop_) {
        cpu_->Exec(kTicks);
    }
}

void Emulator::Stop() {
    stop_ = true;
    thread_.join();
}

} // namespace emu
