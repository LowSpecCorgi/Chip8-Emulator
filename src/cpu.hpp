#pragma once

#include "screen.hpp"

#include <array>
#include <stdexcept>
#include <string>
#include <memory>
#include <algorithm>

// Important constraints for the emmulator
static constexpr uint16_t RAM_SIZE = 4096;
static constexpr uint8_t STACK_SIZE = 16;
static constexpr uint16_t PROGRAM_START = 512;
static constexpr uint16_t REGISTER_NUMBER = 16;

class Cpu {
    public:
        Cpu();

        void load_code(const std::array<uint8_t, RAM_SIZE - PROGRAM_START> code);

        void emulate_cycle();

    protected:
        // Executing instructions

        void execute_instruction(const uint16_t instruction);

        // Convenience functions

        void push_stack(const uint16_t instruction);

        uint16_t pop_stack();

        // Gets the value on the stack where the stack pointer is
        uint16_t get_stack_top() const;

        // This gets a position from ram offsetted by the PROGRAM_START
        uint16_t get_position_in_ram(const uint16_t offset) const;

        // Gets a value from a specified register
        uint16_t get_value_from_reg(const uint8_t reg_position) const;

        // Sets a value in the register to a specified value
        void set_value_in_reg(const uint8_t reg_position, const uint8_t value);

        /*
            Instructions. Since there are quite a few instructions, 
            some with similar traits will be bundled together.
        */

        // nnn = 12 bit memory address
        // nn = 8 bit immediate number

        // Not too sure how to represent 12 bits :(
        bool handle_nnn(const char identifier, const char instruction);

        bool handle_nn(const char identifier, const char instruction);

        bool handle_cls(const char instruction);

        bool handle_dxyn(const char identifier, const char instruction);

    private:
        // Error constants
        const std::string STACK_OVERFLOW_ERR = "STACK OVERFLOW, you cannot exceed the stack size!";
        const std::string STACK_UNDERFLOW_ERR = "STACK UNDERFLOW, stack size cannot go below zero!";
        const std::string OUTSIDE_OF_RAM_ERR = "Trying to access memory outside of the RAM!";
        const std::string OUTSIDE_OF_REG_ERR = "Trying to access memory outside of the registry!";
        const std::string INVALID_INSTRUCTION_ERR = "This instruction is invalid! Instruction: ";

        // The screen
        Screen screen;

        std::array<uint8_t, RAM_SIZE> ram{};

        // Stack: Array of 16 16-bit values
        std::array<uint16_t, STACK_SIZE> stack{};

        // Psuedo-registers

        // Points to the top of the stack
        uint8_t stack_pointer = -1;

        // Stores currently executing address
        uint16_t program_counter = PROGRAM_START;

        // Normal registers

        // 16 8-bit registers numbered V0-VF
        std::array<uint8_t, REGISTER_NUMBER> registers{};

        // Stores memory addresses for use in operations
        uint8_t index_register = 0;

        // The current instruction
        uint16_t opcode = 0;

        // Spriteset
        std::array<uint8_t, 80> spriteset {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };

        // Instruction bit-masks

        // Clears the screen
        const uint16_t CLS = 0x00E0;

        const uint16_t DRAW_IDENTIFIER = 'D';

};