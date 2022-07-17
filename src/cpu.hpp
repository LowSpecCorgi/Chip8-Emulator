#include <array>
#include <stdexcept>
#include <string>

class Cpu {
    public:
        Cpu();
    protected:
        // Convenience functions
        void push_stack(const uint16_t instruction);

        // This gets a position from ram offsetted by the PROGRAM_START
        uint16_t get_position_in_ram(uint16_t offset) const;

    private:
        // Important constraints for the emmulator
        static const uint16_t RAM_SIZE = 4096;
        static const uint8_t STACK_SIZE = 16;
        static const uint16_t PROGRAM_START = 512;

        // Error constants
        const std::string STACK_OVERFLOW_ERR = "STACK OVERFLOW, you cannot exceed the stack size!";

        std::array<uint8_t, RAM_SIZE> ram{};

        // Stack: Array of 16 16-bit values
        std::array<uint16_t, STACK_SIZE> stack{};

        // Psuedo-registers

        // Points to the top of the stack
        uint8_t stack_pointer = 0;

        // Stores currently executing address
        uint16_t program_counter = PROGRAM_START;

        // Normal registers

        // Stores memory addresses for use in operations
        uint8_t index_Register = 0;
};