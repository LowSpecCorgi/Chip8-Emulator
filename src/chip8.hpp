#pragma once

#include "cpu.hpp"

#include <memory>

class Chip8 {
    public:
        Chip8(std::array<uint8_t, RAM_SIZE - PROGRAM_START> code);

        void run();
    private:
        // The CPU, the brain of the emulator
        Cpu cpu = Cpu{};
};