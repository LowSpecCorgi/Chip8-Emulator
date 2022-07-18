#include "chip8.hpp"
#include <memory>

Chip8::Chip8(std::array<uint8_t, RAM_SIZE - PROGRAM_START> code) {
    cpu.load_code(code);
}

void Chip8::run() {
    cpu.emulate_cycle();
}