#include "cpu.hpp"

// Convinience functions

void Cpu::push_stack(const uint16_t instruction) {
    // Check for stack overflow
    if (stack_pointer >= STACK_SIZE) {
        std::throw_with_nested(std::runtime_error(STACK_OVERFLOW_ERR));
    }

    // Push instruction to stack
    stack[stack_pointer] = instruction;
    stack_pointer++;
}

uint16_t Cpu::get_position_in_ram(uint16_t offset) const {
    return offset + PROGRAM_START;
}