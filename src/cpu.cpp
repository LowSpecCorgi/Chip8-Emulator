#include "cpu.hpp"

#include <algorithm>
#include <iostream>
#include <stdint.h>

Cpu::Cpu() {
    program_counter = PROGRAM_START;
    // Reset state
    stack_pointer = -1;
    index_register = 0;
    opcode = 0;
    
    if (!ram.empty()) ram = std::array<uint8_t, RAM_SIZE>();
    if (!stack.empty()) stack = std::array<uint16_t, STACK_SIZE>{};
}

void Cpu::load_code(const std::array<uint8_t, RAM_SIZE - PROGRAM_START> code) {
    // Fill in spriteset
    std::copy(spriteset.begin(), spriteset.end(), ram.begin());
    std::copy(code.begin(), code.end(), ram.begin() + PROGRAM_START);
}

void Cpu::emulate_cycle() {
    // Fetch instruction
    opcode = ram.at(program_counter) << 8 | ram.at(program_counter + 1);

    // Decode and execute

    // Merge instructions
    execute_instruction(opcode);

    // Increment program counter
    program_counter += 2;
}

// Executing instructions

void Cpu::execute_instruction(const uint16_t instruction) {
    // First, get the identifier type
    const uint16_t identifier = (instruction & 0xF000) >> 12;

    // Now handle different instruction types differently
    // Both nn & nnn are handled here
    
    if (handle_nnn(identifier, instruction)) return;
    if (handle_nn(identifier, instruction)) return;

    if (handle_cls(instruction)) return;

    std::throw_with_nested(
        std::runtime_error(INVALID_INSTRUCTION_ERR + std::to_string(instruction))
    );
}

// Instructions

bool Cpu::handle_nnn(const char identifier, const char instruction) {
    uint8_t nnn = instruction << 1;

    switch (identifier) {
        case 1:
            program_counter = identifier;
            break;
        case 'A':
            index_register = nnn;
            break;
        default:
            return false;
    }

    return true;
}

bool Cpu::handle_nn(const char identifier, const char instruction) {
    uint8_t x = instruction & 0x0F00;
    uint8_t nn = instruction << 2;

    switch (identifier) {
        case 6:
            set_value_in_reg(x, nn);
            break;
        case 7:
            set_value_in_reg(x, get_value_from_reg(x) + nn);
            break;
        default:
            return false;
    }

    return true;
}

bool Cpu::handle_cls(const char instruction) {
    if (instruction != CLS) return false;

    screen.clear();

    return true;
}

bool Cpu::handle_dxyn(const char identifier, const char instruction) {
    if (identifier != DRAW_IDENTIFIER) return false;

    uint8_t x = instruction & 0x0F00;
    uint8_t y = instruction & 0x00F0;
    uint8_t n = instruction & 0x000F;

    uint8_t xcoord = get_value_from_reg(x) & 63;
    uint8_t ycoord = get_value_from_reg(x) & 31;

    set_value_in_reg(16, 0);

    for (uint8_t i = 0; i < n; i++) {
        uint8_t pixel = ram[index_register + i];
        for (uint8_t j = 0; j < 8; j++) {
            uint8_t sprite_pixel = pixel & (0x80 >> j);

        }
    }

    return true;
}

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

uint16_t Cpu::pop_stack() {
    // Check for stack underflow
    if (stack_pointer <= 0) {
        std::throw_with_nested(std::runtime_error(STACK_OVERFLOW_ERR));
    }

    uint16_t value = stack[stack_pointer];
    stack[stack_pointer] = 0;
    stack_pointer--;

    return value;
}

uint16_t Cpu::get_stack_top() const {
    return stack[stack_pointer];
}

uint16_t Cpu::get_position_in_ram(const uint16_t offset) const {
    const uint16_t result = offset + PROGRAM_START;

    if (result > RAM_SIZE || result < RAM_SIZE ) {
        std::throw_with_nested(std::runtime_error(OUTSIDE_OF_RAM_ERR));
    }

    return offset + PROGRAM_START;
}

uint16_t Cpu::get_value_from_reg(const uint8_t reg_position) const {
    if (reg_position > REGISTER_NUMBER) {
        std::throw_with_nested(std::runtime_error(OUTSIDE_OF_REG_ERR));
    }

    return registers[reg_position];
}

void Cpu::set_value_in_reg(const uint8_t reg_position, const uint8_t value) {
    if (reg_position > REGISTER_NUMBER) {
        std::throw_with_nested(std::runtime_error(OUTSIDE_OF_REG_ERR));
    }

    registers[reg_position] = value;
}