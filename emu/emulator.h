#ifndef _HOBGOBLIN_EMU_EMUALTOR_H
#define _HOBGOBLIN_EMU_EMUALTOR_H

#include <atomic>
#include <thread>

#include "cpu.h"
#include "device.h"

namespace emu {

class Emulator {
public:
    explicit Emulator(Z80CPU* cpu)
        : stop_(false)
        , cpu_(cpu)
    {}

    void RunBackground();
    void Run();
    void Stop();

private:
    std::atomic<bool> stop_;
    std::thread thread_;
    Z80CPU* cpu_;
};

} // namespace emu

#endif // _HOBGOBLIN_EMU_EMUALTOR_H 
