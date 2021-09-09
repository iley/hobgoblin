#include <cstdio>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/flags/usage.h"

#include "bus.h"
#include "cpu.h"
#include "memory.h"
#include "null_device.h"

using emu::Bus;
using emu::Memory;
using emu::NullDevice;
using emu::Z80CPU;
using emu::Z80Registers;

ABSL_FLAG(std::string, rom_file, "", "ROM file path");

const size_t kAddressSpace = 65536;
const size_t kROMSize = 8192;
const size_t kRAMSize = kAddressSpace - kROMSize;

int main(int argc, char* argv[]) {
    absl::SetProgramUsageMessage("Hobgoblin 8-bit computer emulator.");
    absl::ParseCommandLine(argc, argv);

    const std::string rom_file = absl::GetFlag(FLAGS_rom_file);
    if (rom_file.empty()) {
        fprintf(stderr, "Please specify ROM file via --rom_file\n");
        return 1;
    }

    Memory rom(kROMSize, Memory::AccessMode::READONLY);
    Memory ram(kRAMSize);

    FILE* rom_fd = std::fopen(rom_file.c_str(), "rb");
    if (!rom_fd) {
        fprintf(stderr, "Could not open ROM file '%s': %s\n", rom_file.c_str(), std::strerror(errno));
        return 1;
    }
    rom.Load(rom_fd);
    std::fclose(rom_fd);

    Bus memory_bus;
    memory_bus.Attach(&rom, 0x0000, kROMSize-1);
    memory_bus.Attach(&ram, kROMSize, kAddressSpace-1);

    NullDevice io_bus; // TODO: Add I/O bus.

    Z80CPU cpu(&memory_bus, &io_bus);

    // TODO: Replace with an actual emulation loop.
    for (int i = 0; i < 10; i++) {
        printf("running CPU for 1000 ticks\n");
        cpu.Exec(1000);

        Z80Registers regs = cpu.Registers();
        printf("PC = %d\n", regs.pc);
    }

    return 0;
}
