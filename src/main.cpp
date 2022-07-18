#include "chip8.hpp"

#include <array>
#include <memory>
#include <iostream>

int main() {
    // Code
    auto code = std::array<uint8_t, RAM_SIZE - PROGRAM_START>{0x10, 0x22};

    // Create emulator
    auto chip8 = std::make_unique<Chip8>(code);

    try {
        chip8->run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}