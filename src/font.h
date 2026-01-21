#pragma once

#include <gb/gb.h>
#include <stdint.h>

#define font_letter_spacing 1
#define font_space_width 2

// Returns the width of a character in pixels, or `0` if no character was found.
uint8_t font_get_character_width(char c);

// Returns the width of a string, up to the end of a string or new-line.
uint8_t font_get_line_width(const char *string);

// Render character data into a single 1bpp tile.
void font_render_char_data_1bpp(uint8_t *tile, int8_t dx, int8_t dy, const uint8_t *char_data);

// Render character data spanning two adjacent 1bpp tiles.
void font_render_char_data_1bpp_span(uint8_t *tile1, uint8_t *tile2, int8_t dx, int8_t dy, const uint8_t *char_data);

// Render a character into a 1bpp tile at a given destination in pixels. Writes
// high pixels into the tile, safely cropping any pixels outside the tile.
//
// The width of the character is returned, or `0` if no character was found.
// Implementation assumes empty destination buffers, only high bits are written.
uint8_t font_render_character_1bpp(uint8_t *tile, int8_t dx, int8_t dy, char c);

typedef struct {
  const char *remainder;
  uint8_t pixel_count;
  uint8_t tile_count;
} font_render_line_result_t;

// Render a string into a 1bpp tile buffer.
//
// Characters from the string are rendered using font_render_character_1bpp,
// starting at dx & dy. Characters are rendered until the end of the string, the
// end of the line or the end of the available tiles.
//
// Once the end is reached, `remainder` is returned, representing a pointer to
// the next character in the string not rendered, or the end of the string.
// Additionally, the amount of tiles written to is returned as `tile_count`, and
// the amount of pixels rendered is returned as `pixel_count`.
font_render_line_result_t font_render_line_1bpp(
  uint8_t *tiles,
  uint8_t tiles_length,
  int8_t dx,
  int8_t dy,
  const char *string
);
