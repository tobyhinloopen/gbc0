#include "font_test.h"
#include "minunit.h"
#include "font.h"
#include "font_data.h"
#include <string.h>

#define tile_data_length 20
static uint8_t tile_data[tile_data_length * 8];
static const uint8_t *bench_char_data;

static void reset_tile_data(void) {
  memset(tile_data, 0, sizeof(tile_data));
}

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

static char *test_font_render_character_1bpp_known_width(void) {
  mu_assert_eq(render('!'), 1, "%d"); // Known 1-pixel wide
  return 0;
}

static char *test_font_render_character_1bpp_known_data(void) {
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
  font_render_line_result_t result = font_render_line_1bpp(tile_data, tile_data_length, 0, 0, "Hi");

  uint8_t expected_pixels = font_get_line_width("Hi");
  uint8_t expected_tiles = (expected_pixels + 7) / 8;

  mu_assert_eq(*result.remainder, '\0', "%c");
  mu_assert_eq(result.pixel_count, expected_pixels, "%d");
  mu_assert_eq(result.tile_count, expected_tiles, "%d");

  return 0;
}

static char *test_font_render_line_1bpp_too_long(void) {
  const uint8_t short_length = 4;
  const char *text = "This is a long string!";
  font_render_line_result_t result = font_render_line_1bpp(tile_data, short_length, 0, 0, text);

  mu_assert(*result.remainder != '\0');
  mu_assert(result.remainder > text);
  mu_assert_eq(result.tile_count, short_length, "%d");
  mu_assert(result.pixel_count <= short_length * 8);

  return 0;
}

static char *test_font_get_line_width(void) {
  mu_assert_eq(font_get_line_width(""), 0, "%d");

  uint8_t expected = font_get_character_width('H') + font_letter_spacing + font_get_character_width('i');
  mu_assert_eq(font_get_line_width("Hi"), expected, "%d");
  mu_assert_eq(font_get_line_width("Hi\nWorld"), expected, "%d");

  return 0;
}

static char *bench_font_render_character_1bpp(void) {
  font_render_character_1bpp(tile_data, 0, 0, 'W');
  return 0;
}

static char *bench_font_render_line_1bpp(void) {
  font_render_line_1bpp(tile_data, tile_data_length, 0, 0, "Hello, world!");
  return 0;
}

static char *bench_font_render_char_data_1bpp(void) {
  font_render_char_data_1bpp(tile_data, 0, 0, bench_char_data);
  return 0;
}

static char *bench_font_render_char_data_1bpp_span(void) {
  font_render_char_data_1bpp_span(tile_data, &tile_data[8], 4, 0, bench_char_data);
  return 0;
}

char *font_test(void) {
  mu_before_each = reset_tile_data;
  bench_char_data = font_data_get('W');
  mu_run_test(test_font_render_character_1bpp_missing_character);
  mu_run_test(test_font_render_character_1bpp_known_width);
  mu_run_test(test_font_render_character_1bpp_known_data);
  mu_run_test(test_font_render_line_1bpp_simple);
  mu_run_test(test_font_render_line_1bpp_too_long);
  mu_run_test(test_font_get_line_width);
  mu_run_bench("render_char", bench_font_render_character_1bpp);
  mu_run_bench("render_line", bench_font_render_line_1bpp);
  mu_run_bench("char_data", bench_font_render_char_data_1bpp);
  mu_run_bench("char_span", bench_font_render_char_data_1bpp_span);
  return 0;
}
