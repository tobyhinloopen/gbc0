#pragma once

#include <stdint.h>

#define font_data_ascii_offset 33
#define font_data_ascii_max 126

extern const uint8_t font_data[599];
extern const uint16_t font_data_indices[94];

const uint8_t *font_data_get(char c);

#define FONT_DATA_WIDTH(char_data) ((char_data)[0] & 0x07)
#define FONT_DATA_HEIGHT(char_data) (((char_data)[0] >> 3) & 0x07)
#define FONT_DATA_VERTICAL_OFFSET(char_data) \
  ((((char_data)[0] >> 6) & 0x03) | (((char_data)[1] & 0x01) << 2))
