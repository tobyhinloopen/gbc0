#pragma once

#include <gb/gb.h>
#include <stdint.h>

// Render a character into a 1bpp tile buffer at a given destination in pixels,
// relative to top/left of the tile. Writes into 1 or 2 tiles in `tile`.
// The width of the character is returned, or `0` if nothing was rendered.
// Implementation assumes empty destination buffers, only high bits are written.
uint8_t font_render_character_1bpp(uint8_t *tile, int8_t dx, int8_t dy, char c);
