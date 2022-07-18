#pragma once

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

        void load_code(std::array<uint8_t, RAM_SIZE - PROGRAM_START> code);

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
        bool handle_nnn(const char identifier, const uint8_t nnn);

        bool handle_nn(const char identifier, const uint8_t x, const uint8_t nn);

    private:
        // Error constants
        const std::string STACK_OVERFLOW_ERR = "STACK OVERFLOW, you cannot exceed the stack size!";
        const std::string STACK_UNDERFLOW_ERR = "STACK UNDERFLOW, stack size cannot go below zero!";
        const std::string OUTSIDE_OF_RAM_ERR = "Trying to access memory outside of the RAM!";
        const std::string OUTSIDE_OF_REG_ERR = "Trying to access memory outside of the registry!";
        const std::string INVALID_INSTRUCTION_ERR = "This instruction is invalid! Instruction: ";

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

        // Instruction bit-masks

};