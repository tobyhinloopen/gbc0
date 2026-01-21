#include "font_test.h"
#include "minunit.h"
#include "font.h"
#include "font_data.h"
#include <string.h>

#define tile_data_length 4
static uint8_t tile_data[tile_data_length * 8];

static uint8_t render(char c) {
  return font_render_character_1bpp(tile_data, 0, 0, c);
}

static char *test_font_render_character_1bpp_missing_character(void) {
  mu_assert_eq(render(' '), 0, "%d"); // Test a space
  mu_assert_eq(render('@'), 0, "%d"); // Test a known missing character
  mu_assert_eq(render(200), 0, "%d"); // Test beyond 7-bit ascii range
  mu_assert_eq(render(18), 0, "%d"); // Test before visible characters
  return 0;
}

static char *test_font_render_character_1bpp_known_character(void) {
  mu_assert_eq(render('!'), 1, "%d"); // Known 1-pixel wide

  memset(tile_data, 0, sizeof(tile_data));
  mu_assert_eq(render('#'), 5, "%d"); // Known 5-pixel wide
  mu_assert_eq(tile_data[0], 0b00000000, "%d");
  mu_assert_eq(tile_data[1], 0b01010000, "%d");
  mu_assert_eq(tile_data[2], 0b11111000, "%d");
  mu_assert_eq(tile_data[3], 0b01010000, "%d");
  mu_assert_eq(tile_data[4], 0b11111000, "%d");
  mu_assert_eq(tile_data[5], 0b01010000, "%d");
  mu_assert_eq(tile_data[6], 0b00000000, "%d");
  mu_assert_eq(tile_data[7], 0b00000000, "%d");

  return 0;
}

static char *test_font_render_line_1bpp_simple(void) {
  memset(tile_data, 0, sizeof(tile_data));
  font_render_line_result_t result = font_render_line_1bpp(tile_data, tile_data_length, 0, 0, "Hi");

  uint8_t expected_pixels = font_get_character_width('H') + font_letter_spacing + font_get_character_width('i');
  uint8_t expected_tiles = (expected_pixels + 7) / 8;

  mu_assert_eq(*result.remainder, '\0', "%c");
  mu_assert_eq(result.pixel_count, expected_pixels, "%d");
  mu_assert_eq(result.tile_count, expected_tiles, "%d");

  return 0;
}

static char *test_font_render_line_1bpp_too_long(void) {
  // memset(tile_data, 0, sizeof(tile_data));
  // font_render_line_result_t result = font_render_line_1bpp(tile_data, tile_data_length, 0, 0, "This is a long string!");

  // assert the remainer, pixel count and tile count
}

char *font_test(void) {
  mu_run_test(test_font_render_character_1bpp_missing_character);
  mu_run_test(test_font_render_character_1bpp_known_character);
  mu_run_test(test_font_render_line_1bpp_simple);
  mu_run_test(test_font_render_line_1bpp_too_long);
  return 0;
}
