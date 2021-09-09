#include <cstdio>

#define CATCH_CONFIG_MAIN
#include "third_party/catch.hpp"

#include "bus.h"
#include "memory.h"

namespace emu {

TEST_CASE("bus with single device") {
    Memory ram(4);
    ram.Load({0xDE, 0xAD, 0xBE, 0xEF});

    Bus bus;
    bus.Attach(&ram, 4, 7);

    SECTION("read") {
        REQUIRE(bus.Read(4) == 0xDE);
        REQUIRE(bus.Read(5) == 0xAD);
        REQUIRE(bus.Read(6) == 0xBE);
        REQUIRE(bus.Read(7) == 0xEF);
    }

    SECTION("write") {
        bus.Write(4, 0xFF);

        REQUIRE(bus.Read(4) == 0xFF);
        REQUIRE(ram.Read(0) == 0xFF);
    }
}

TEST_CASE("bus with multiple devices") {
    Memory ram1(2);
    ram1.Load({0xDE, 0xAD});

    Memory ram2(2);
    ram2.Load({0xBE, 0xEF});

    Bus bus;
    bus.Attach(&ram1, 4, 5);
    bus.Attach(&ram2, 6, 7);

    SECTION("read") {
        REQUIRE(bus.Read(4) == 0xDE);
        REQUIRE(bus.Read(5) == 0xAD);
        REQUIRE(bus.Read(6) == 0xBE);
        REQUIRE(bus.Read(7) == 0xEF);
    }

    SECTION("out of range access") {
        REQUIRE(bus.Read(0) == 0);
        REQUIRE(bus.Read(8) == 0);
        REQUIRE(bus.Read(0xFFFF) == 0);
    }
}

} // namespace emu
