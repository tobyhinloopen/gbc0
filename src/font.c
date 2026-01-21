#include "font.h"
#include "font_data.h"

#include <stdio.h>

#define FONT_RENDER_LOOP(char_data, width, dy, ROW_HANDLER)                   \
  do {                                                                        \
    uint8_t height = FONT_DATA_HEIGHT(char_data);                             \
    dy += FONT_DATA_VERTICAL_OFFSET(char_data);                               \
    uint8_t bit_index = 9;                                                    \
    uint8_t width_mask = (1 << width) - 1;                                    \
    for (uint8_t y = 0; y < height; y++, bit_index += width) {                \
      int8_t py = dy + (int8_t)y;                                             \
      if (py < 0 || py >= 8)                                                  \
        continue;                                                             \
      uint8_t row = ((char_data[bit_index >> 3] |                             \
        ((uint16_t)char_data[(bit_index >> 3) + 1] << 8)) >>                  \
        (bit_index & 7)) & width_mask;                                        \
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

static void font_render_char_data_1bpp(
  uint8_t *tile, int8_t dx, int8_t dy,
  const uint8_t *char_data
) {
  uint8_t width = FONT_DATA_WIDTH(char_data);
  int8_t shift = 8 - dx - width;
  FONT_RENDER_LOOP(char_data, width, dy,
    if (shift >= 0)
      tile[py] |= row << shift;
    else
      tile[py] |= row >> (-shift);
  );
}

static void font_render_char_data_1bpp_span(
  uint8_t *tile1, uint8_t *tile2,
  int8_t dx, int8_t dy,
  const uint8_t *char_data
) {
  uint8_t width = FONT_DATA_WIDTH(char_data);
  int8_t shift1 = 8 - dx - width;
  int8_t shift2 = shift1 + 8;
  FONT_RENDER_LOOP(char_data, width, dy,
    tile1[py] |= row >> (-shift1);
    tile2[py] |= row << shift2;
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
