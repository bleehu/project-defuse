#pragma once

#include "pico/stdlib.h"

// This represents the display data as raw bits to be sent to the shift registers.
struct Display
{
    uint32_t digits[7];
};

Display string_to_display(const char16_t* str);
Display string_to_display(const char* str);

// Call this to setup the display, before calling update_display()
void init_display();

void update_display(Display display);
// Convenience functions to update the display straight from a string
void update_display(const char16_t* str);
void update_display(const char* str);

enum Marks : uint16_t
{
    DOT_TOP_LEFT = 0x80,
    GRAVE = 0x40,
    ACUTE = 0x20,
    DOT_TOP_RIGHT = 0x10,
    BOTTOM_RIGHT = 0x8,
    BOTTOM_MIDDLE = 0x4,
    BOTTOM_LEFT = 0x2,
    DECIMAL_POINT = 0x100,
    TOP_OF_COLON = 0x200
};
void add_marks_to_digit(Display& display, int digit, uint16_t marks);