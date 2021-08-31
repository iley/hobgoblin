#define CATCH_CONFIG_MAIN
#include "vendor/catch.hpp"

#include "memory.h"

namespace emu {

TEST_CASE("RAM read/write") {
    Memory ram(4);

    // RAM is always initialized with zeroes.
    REQUIRE(ram.Read(0) == 0);

    ram.Write(0, 42);
    REQUIRE(ram.Read(0) == 42);

    // Out-of-bounds access.
    ram.Write(8, 0xff);
    REQUIRE(ram.Read(8) == 0);
}

TEST_CASE("RAM load") {
    const std::vector<uint8_t> source_data({1, 2, 3});
    Memory ram(10);

    SECTION("complete load") {
        const uint16_t loaded_bytes = ram.Load(source_data);

        REQUIRE(loaded_bytes == 3);
        REQUIRE(ram.Read(0) == 1);
        REQUIRE(ram.Read(1) == 2);
        REQUIRE(ram.Read(2) == 3);
    }

    SECTION("partial load") {
        const uint16_t loaded_bytes = ram.Load(source_data, 8);

        REQUIRE(loaded_bytes == 2);
        REQUIRE(ram.Read(8) == 1);
        REQUIRE(ram.Read(9) == 2);
    }

    SECTION("load from file") {
        FILE* file = std::tmpfile();
        REQUIRE(file != nullptr);
        const size_t written_bytes = std::fwrite(source_data.data(), sizeof(uint8_t), source_data.size(), file);
        REQUIRE(written_bytes == 3);
        std::fseek(file, 0, SEEK_SET);

        const uint16_t loaded_bytes = ram.Load(file);

        REQUIRE(loaded_bytes == 3);
        REQUIRE(ram.Read(0) == 1);
        REQUIRE(ram.Read(1) == 2);
        REQUIRE(ram.Read(2) == 3);

        fclose(file);
    }
}

} // namespace emu
