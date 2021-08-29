#define CATCH_CONFIG_MAIN
#include "vendor/catch.hpp"

#include "cpu.h"
#include "memory.h"
#include "null_device.h"

namespace emu {

TEST_CASE("NOP") {
    Memory ram(0x10000); // full 64k
    ram.Write(0x0000, 0x00); // NOP

    NullDevice nulldev; // dummy I/O

    Z80CPU cpu(&ram, &nulldev);

    uint32_t executed_ticks = cpu.Exec(4); // NOP takes 4 ticks
    REQUIRE(executed_ticks == 4);

    const auto registers = cpu.Registers();
    REQUIRE(registers.pc == 1);
}

} // namespace emu
