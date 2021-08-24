#define CATCH_CONFIG_MAIN
#include "vendor/catch.hpp"

#include "memory.h"

TEST_CASE("RAM access") {
    emu::RAM ram(4);

    // RAM is always initialized with zeroes.
    REQUIRE(ram.Read(0) == 0);

    ram.Write(0, 42);
    REQUIRE(ram.Read(0) == 42);

    // Out-of-bounds access.
    ram.Write(8, 0xff);
    REQUIRE(ram.Read(8) == 0);
}
