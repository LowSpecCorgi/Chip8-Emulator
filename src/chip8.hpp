#include "cpu.hpp"

class Chip8 {
    public:
        Chip8();
    private:
        // The CPU, the brain of the emulator
        Cpu cpu = Cpu{};
};