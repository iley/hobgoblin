#include <cstdio>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/flags/usage.h"
#include "absl/status/status.h"
#include "absl/strings/str_format.h"

#include "bus.h"
#include "cpu.h"
#include "emulator.h"
#include "mc6850.h"
#include "memory.h"

ABSL_FLAG(std::string, rom_file, "", "ROM file path");

const size_t kAddressSpace = 65536;
const size_t kROMSize = 8192;
const size_t kRAMSize = kAddressSpace - kROMSize;

namespace emu {

absl::Status RunEmulator(const std::string& rom_file) {
    Memory rom(kROMSize, Memory::AccessMode::READONLY);
    Memory ram(kRAMSize);

    FILE* rom_fd = std::fopen(rom_file.c_str(), "rb");
    if (!rom_fd) {
        return absl::Status(
            absl::StatusCode::kInvalidArgument,
            absl::StrFormat("Could not open ROM file '%s': %s", rom_file, std::strerror(errno)));
    }
    rom.Load(rom_fd);
    std::fclose(rom_fd);

    Bus memory_bus;
    memory_bus.Attach(&rom, 0x0000, kROMSize-1);
    memory_bus.Attach(&ram, kROMSize, kAddressSpace-1);

    MC6850 serial;

    Bus io_bus;
    io_bus.Attach(&serial, 0x80, 0x81);

    Z80CPU cpu(&memory_bus, &io_bus);
    cpu.AddInterruptSource(&serial);

    Emulator emulator(&cpu);
    emulator.RunBackground();

    // TODO: Figure out how to gracefully shut down this thread.
    std::thread output_thread([&serial]() {
        while (true) {
            uint8_t ch = serial.Receive();
            std::fputc(ch, stdout);
        }
    });

    while (true) {
        int ch = fgetc(stdin);
        if (ch == EOF) {
            break;
        }
        serial.Send(ch);
    }

    emulator.Stop();

    auto regs = cpu.Registers();
    std::cout << "PC = " << regs.pc << std::endl;

    return absl::OkStatus();
}

} // namespace emu

int main(int argc, char* argv[]) {
    absl::SetProgramUsageMessage("Hobgoblin 8-bit computer emulator.");
    absl::ParseCommandLine(argc, argv);

    const std::string rom_file = absl::GetFlag(FLAGS_rom_file);
    if (rom_file.empty()) {
        std::cerr << "Please specify ROM file via --rom_file" << std::endl;
        return 1;
    }

    absl::Status status = emu::RunEmulator(rom_file);
    if (!status.ok()) {
        std::cerr << "emulator error: " << status << std::endl;
        return 1;
    }

    return 0;
}
