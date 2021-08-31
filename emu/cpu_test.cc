#define CATCH_CONFIG_MAIN
#include "vendor/catch.hpp"

#include "cpu.h"
#include "memory.h"
#include "null_device.h"

namespace emu {

uint8_t hi(uint16_t val) {
    return (val >> 8) & 0xff;
}

TEST_CASE("basics") {
    Memory ram(0x100);   // 256 bytes of RAM
    NullDevice nulldev;  // dummy I/O
    Z80CPU cpu(&ram, &nulldev);

    SECTION("NOP") {
        ram.Write(0x0000, 0x00); // NOP

        uint32_t executed_ticks = cpu.Exec(4); // NOP takes 4 ticks
        REQUIRE(executed_ticks == 4);

        const auto registers = cpu.Registers();
        REQUIRE(registers.pc == 1);
    }

    SECTION("1 + 1") {
        ram.WriteBlock(0x0000, {
            0x3e, 0x01, // LD A, 1 (7 ticks)
            0x3c,       // INC A   (4 ticks)
        });

        uint32_t executed_ticks = cpu.Exec(11);
        REQUIRE(executed_ticks == 11);

        const auto registers = cpu.Registers();
        REQUIRE(registers.a() == 2);
        REQUIRE(registers.pc == 3);
    }
}

} // namespace emu
