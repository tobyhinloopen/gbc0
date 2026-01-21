#include "font.h"
#include "font_data.h"

#include <stdio.h>

// New format: byte 0-1 = metadata (same as before), byte 2+ = one byte per row
#define FONT_RENDER_LOOP(char_data, width, dy, ROW_HANDLER)                   \
  do {                                                                        \
    uint8_t height = FONT_DATA_HEIGHT(char_data);                             \
    dy += FONT_DATA_VERTICAL_OFFSET(char_data);                               \
    const uint8_t *row_ptr = char_data + 2;                                   \
    for (uint8_t y = 0; y < height; y++, row_ptr++) {                         \
      int8_t py = dy + (int8_t)y;                                             \
      if (py < 0 || py >= 8)                                                  \
        continue;                                                             \
      uint8_t row = *row_ptr;                                                 \
      ROW_HANDLER                                                             \
    }                                                                         \
  } while (0)

uint8_t font_get_character_width(char c) {
  const uint8_t *char_data = font_data_get(c);
  return char_data ? FONT_DATA_WIDTH(char_data) : 0;
}

uint8_t font_get_line_width(const char *string) {
  uint8_t width = 0;
  while (*string && *string != '\n') {
    uint8_t w = font_get_character_width(*string);
    if (w > 0)
      width += w + font_letter_spacing;
    string++;
  }
  return width > 0 ? width - font_letter_spacing : 0;
}

void font_render_char_data_1bpp(
  uint8_t *tile, int8_t dx, int8_t dy,
  const uint8_t *char_data
) {
  uint8_t width = FONT_DATA_WIDTH(char_data);
  int8_t shift = 8 - dx - width;
  if (shift >= 0) {
    FONT_RENDER_LOOP(char_data, width, dy,
      tile[py] |= row << shift;
    );
  } else {
    shift = -shift;
    FONT_RENDER_LOOP(char_data, width, dy,
      tile[py] |= row >> shift;
    );
  }
}

void font_render_char_data_1bpp_span(
  uint8_t *tile1, uint8_t *tile2,
  int8_t dx, int8_t dy,
  const uint8_t *char_data
) {
  uint8_t width = FONT_DATA_WIDTH(char_data);
  uint8_t rshift = dx + width - 8;
  uint8_t lshift = 8 - rshift;
  FONT_RENDER_LOOP(char_data, width, dy,
    tile1[py] |= row >> rshift;
    tile2[py] |= row << lshift;
  );
}

uint8_t font_render_character_1bpp(uint8_t *tile, int8_t dx, int8_t dy, char c) {
  const uint8_t *char_data = font_data_get(c);
  if (!char_data)
    return 0;

  font_render_char_data_1bpp(tile, dx, dy, char_data);
  return FONT_DATA_WIDTH(char_data);
}

font_render_line_result_t font_render_line_1bpp(
  uint8_t *tiles,
  uint8_t tiles_length,
  int8_t dx,
  int8_t dy,
  const char *string
) {
  uint8_t x = dx;
  const char *current_char = string;

  while (*current_char) {
    char c = *current_char;

    if (c == '\n')
      break;

    if (c == ' ') {
      x += font_space_width;
      current_char++;
      continue;
    }

    uint8_t tile_x = x / 8;
    int8_t offset_x = x % 8;

    if (tile_x >= tiles_length)
      break;

    const uint8_t *char_data = font_data_get(c);
    if (!char_data) {
      current_char++;
      continue;
    }

    uint8_t w = FONT_DATA_WIDTH(char_data);
    uint8_t *tile1 = &tiles[tile_x * 8];

    if (offset_x + w > 8 && tile_x + 1 < tiles_length)
      font_render_char_data_1bpp_span(tile1, &tiles[(tile_x + 1) * 8], offset_x, dy, char_data);
    else
      font_render_char_data_1bpp(tile1, offset_x, dy, char_data);

    x += w + font_letter_spacing;
    current_char++;
  }

  uint8_t rendered_width = (uint8_t)(x - dx);

  font_render_line_result_t result;
  result.remainder = current_char;
  result.pixel_count = rendered_width > 0 ? rendered_width - font_letter_spacing : 0;
  result.tile_count = (uint8_t)((x + 7) / 8);

  return result;
}
