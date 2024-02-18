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

