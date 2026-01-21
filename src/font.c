#include "font.h"
#include "font_data.h"

#include <stdio.h>

uint8_t font_render_character_1bpp(uint8_t *tile, int8_t dx, int8_t dy, char c) {
  if (c < font_data_ascii_offset
  || c > font_data_ascii_max)
    return 0;

  uint16_t i = font_data_indices[(uint8_t)c - font_data_ascii_offset];
  if (i == 0)
    return 0;

  uint8_t *char_data = &font_data[i];
  uint8_t width = char_data[0] & 0x07;
  uint8_t height = (char_data[0] >> 3) & 0x07;
  dy += ((char_data[0] >> 6) & 0x03) | ((char_data[1] & 0x01) << 2);

  uint8_t bit_index = 9;

  // TODO: Copy row-by-row, not pixel-by-pixel
  // TODO: Test dx/dy beyond tile boundaries (both negative and positive)
  for (uint8_t y = 0; y < height; y++) {
    int8_t py = dy + (int8_t)y;

    if (py < 0 || py >= 8)
      continue;

    for (uint8_t x = 0; x < width; x++, bit_index++) {
      int8_t px = dx + (int8_t)x;

      if (px < 0
      || px >= 8
      || !((char_data[bit_index >> 3] >> (bit_index & 7)) & 1u))
        continue;

      tile[py] |= (uint8_t)(1u << (7 - px));
    }
  }

  return width;
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

    uint8_t w = font_render_character_1bpp(&tiles[tile_x * 8], offset_x, dy, c);

    if (offset_x + w > 8 && tile_x + 1 < tiles_length) {
      offset_x -= 8;
      tile_x++;
      font_render_character_1bpp(&tiles[tile_x * 8], offset_x, dy, c);
    }

    x += w + font_letter_spacing;
    current_char++;
  }

  font_render_line_result_t result;
  result.remainder = current_char;
  result.pixel_count = (uint8_t)(x - dx);
  result.tile_count = (uint8_t)((x + 7) / 8);

  return result;
}
