#pragma once

#include <stdint.h>

// Global cursor state (pixel positions)
extern uint8_t font_cursor_x;
extern uint8_t font_cursor_y;

// Reset cursor and tile allocation
void font_clear(void);

// Print text at cursor position, updating cursor afterward
void font_print(const char *text);

// Printf-style formatted output at cursor position
void font_printf(const char *fmt, ...);
