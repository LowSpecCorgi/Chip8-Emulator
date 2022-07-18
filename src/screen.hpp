#pragma once

#include <algorithm>
#include <memory>
#include <array>
#include <exception>
#include <string>

class Screen {
    public:
        Screen();

        void set_pixel(const uint8_t x, const uint8_t y, const bool value);
        bool get_pixel(const uint8_t x, const uint8_t y) const;
        void clear();
                
        static const uint8_t SCREEN_WIDTH = 64;
        static const uint8_t SCREEN_HEIGHT = 32;

    protected:
        void throw_if_outside_of_screen(const uint8_t x, const uint8_t y) const;

        const std::string OUTSIDE_OF_SCREEN_ERR = "Trying to set a pixel outside of the screen!";

        std::array<std::array<bool, SCREEN_WIDTH>, SCREEN_HEIGHT> screen = {};
};