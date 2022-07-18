#include "screen.hpp"

#include <exception>
#include <stdexcept>

Screen::Screen() {}

void Screen::set_pixel(const uint8_t x, const uint8_t y, const bool value) {
    throw_if_outside_of_screen(x, y);
    
    screen[y][x] = value;
}

bool Screen::get_pixel(const uint8_t x, const uint8_t y) const {
    throw_if_outside_of_screen(x, y);

    return screen[y][x];
}

void Screen::clear() {
    screen.fill({});
}

void Screen::throw_if_outside_of_screen(const uint8_t x, const uint8_t y) const {
    if (x > SCREEN_WIDTH || y > SCREEN_HEIGHT || x < 0 || y < 0) {
        std::throw_with_nested(std::runtime_error(OUTSIDE_OF_SCREEN_ERR));
    }
}