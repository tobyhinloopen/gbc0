#include "font_stdio.h"
#include "font.h"
#include <gb/gb.h>
#include <string.h>
#include <stdarg.h>

#define CONSOLE_WIDTH 20
#define CONSOLE_HEIGHT 18
#define CONSOLE_TILE_START 128
#define CONSOLE_TILE_MAX 256
#define TILE_SIZE 8

uint8_t font_cursor_x = 0;
uint8_t font_cursor_y = 0;
static uint16_t next_tile_index = CONSOLE_TILE_START;

static uint8_t line_tiles[TILE_SIZE * CONSOLE_WIDTH];

static font_render_line_result_t render_line_to_vram(uint8_t row, const char *text, uint8_t max_width, uint8_t dx) {
  memset(line_tiles, 0, sizeof(line_tiles));
  font_render_line_result_t result = font_render_line_1bpp(line_tiles, CONSOLE_WIDTH, max_width, dx, 0, text);

  if (next_tile_index + result.tile_count > CONSOLE_TILE_MAX)
    next_tile_index = CONSOLE_TILE_START;

  uint16_t tile_index = next_tile_index;
  next_tile_index += result.tile_count;
  set_bkg_1bpp_data(tile_index, result.tile_count, line_tiles);
  for (uint8_t x = 0; x < result.tile_count; x++)
    set_bkg_tile_xy(x, row, tile_index + x);

  return result;
}

void font_clear(void) {
  next_tile_index = CONSOLE_TILE_START;
  font_cursor_x = 0;
  font_cursor_y = 0;
}

void font_print(const char *text) {
  uint8_t row = font_cursor_y / 8;
  uint8_t dx = font_cursor_x;
  uint8_t max_width = CONSOLE_WIDTH * 8;

  while (*text && row < CONSOLE_HEIGHT) {
    font_render_line_result_t result = render_line_to_vram(row, text, max_width, dx);

    text = result.remainder;
    if (*text == '\n')
      text++;

    row++;
    dx = 0;
  }

  font_cursor_x = 0;
  font_cursor_y = row * 8;
}

static char fmt_buffer[64];

static char *format_int(char *buf, int16_t val, uint8_t base, uint8_t uppercase) {
  char *p = buf + 20;
  *--p = '\0';

  uint8_t negative = 0;
  uint16_t uval;

  if (val < 0 && base == 10) {
    negative = 1;
    uval = -val;
  } else {
    uval = (uint16_t)val;
  }

  do {
    uint8_t digit = uval % base;
    if (digit < 10)
      *--p = '0' + digit;
    else
      *--p = (uppercase ? 'A' : 'a') + digit - 10;
    uval /= base;
  } while (uval);

  if (negative)
    *--p = '-';

  return p;
}

void font_printf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);

  char *out = fmt_buffer;
  char *end = fmt_buffer + sizeof(fmt_buffer) - 1;

  while (*fmt && out < end) {
    if (*fmt != '%') {
      *out++ = *fmt++;
      continue;
    }

    fmt++;
    switch (*fmt) {
      case 'd':
      case 'i': {
        int16_t val = va_arg(args, int);
        char *s = format_int(out, val, 10, 0);
        while (*s && out < end)
          *out++ = *s++;
        fmt++;
        break;
      }
      case 'u': {
        uint16_t val = va_arg(args, unsigned int);
        char *s = format_int(out, val, 10, 0);
        while (*s && out < end)
          *out++ = *s++;
        fmt++;
        break;
      }
      case 'x': {
        uint16_t val = va_arg(args, unsigned int);
        char *s = format_int(out, val, 16, 0);
        while (*s && out < end)
          *out++ = *s++;
        fmt++;
        break;
      }
      case 'X': {
        uint16_t val = va_arg(args, unsigned int);
        char *s = format_int(out, val, 16, 1);
        while (*s && out < end)
          *out++ = *s++;
        fmt++;
        break;
      }
      case 's': {
        const char *s = va_arg(args, const char *);
        while (*s && out < end)
          *out++ = *s++;
        fmt++;
        break;
      }
      case 'c': {
        char c = (char)va_arg(args, int);
        *out++ = c;
        fmt++;
        break;
      }
      case '%':
        *out++ = '%';
        fmt++;
        break;
      default:
        *out++ = '%';
        break;
    }
  }

  *out = '\0';
  va_end(args);

  font_print(fmt_buffer);
}
