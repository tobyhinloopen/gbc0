#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include "grid.h"
#include "rand.h"
#include "renderer.h"
#include "test.h"
#include "font.h"
#include "font_data.h"
#include <string.h>

#define _tile_size 8
#define _char_count 94

static uint8_t tile_data[_tile_size * _char_count];

static void render_font_characters(void) {
  memset(tile_data, 0, sizeof(tile_data));

  for (uint8_t i = 0; i < _char_count; i++)
    font_render_character_1bpp(&tile_data[i * _tile_size], 0, 0, font_data_ascii_offset + i);
  set_bkg_1bpp_data(1, _char_count, tile_data);

  for (uint8_t y = 0; y < 8; y++)
    for (uint8_t x = 0; x < 12; x++)
      if (y * 12 + x < _char_count)
        set_bkg_tile_xy(x + 1, y + 1, 1 + y * 12 + x);
}

static void render_line(const char *text) {
  uint8_t text_tile_data[_tile_size * 20];
  memset(text_tile_data, 0, sizeof(text_tile_data));
  size_t len = strlen(text);

  uint16_t x = 0;
  for (size_t i = 0; i < len; i++) {
    char c = text[i];
    if (c == ' ') {
      x+=2;
      continue;
    }
    uint16_t tile_x = x / _tile_size;
    int8_t offset_x = x % _tile_size;
    int8_t w = font_render_character_1bpp(&text_tile_data[tile_x * _tile_size], offset_x, 0, c);

    if (offset_x + w > 8) {
      offset_x -= 8;
      tile_x++;
      font_render_character_1bpp(&text_tile_data[tile_x * _tile_size], offset_x, 0, c);
    }

    x += w + 1;
  }

  set_bkg_1bpp_data(100, 20, text_tile_data);

  for (uint8_t i = 0; i < 20; i++)
    set_bkg_tile_xy(i, 10, 100 + i);
}

const uint16_t bg_palette0[4] = { 0x7FFF, 0x001F, 0x03E0, 0x7C00 };
const uint16_t bg_palette1[4] = { 0x001F, 0x7FFF, 0x03E0, 0x7C00 };

void main(void) {
  DISPLAY_ON;
  SHOW_BKG;
  // SHOW_WIN;

  // WX_REG = (uint8_t)(152 + 7);
  // WY_REG = 0;

  if (_cpu == CGB_TYPE) {
    // TODO: Enable this, but disabled for now so performance issues show faster
    // cpu_fast();
    set_bkg_palette(0, 1, bg_palette0);
    // set_bkg_palette(1, 1, bg_palette1);
    // set_bkg_palette(2, 1, bg_palette0);
    // set_bkg_palette(3, 1, bg_palette1);
    // set_bkg_palette(4, 1, bg_palette0);
    // set_bkg_palette(5, 1, bg_palette1);
  } else {
    BGP_REG = 0xE4;
  }

  rand_init();

  // set_bkg_data(1, 1, renderer_tile);

  // VBK_REG = VBK_TILES;
  // for (uint8_t i = 1; i <= 7; i++)
  //   set_bkg_tile_xy(i, 0, 1);

  // VBK_REG = VBK_ATTRIBUTES;
  // for (uint8_t i = 1; i <= 7; i++)
  //   set_bkg_tile_xy(i, 0, i);
  // VBK_REG = VBK_TILES;

  // if (test_main()) {
  //   vsync();
  //   return;
  // }

  render_font_characters();
  render_line(" Hello, world!! This is a variable-width string!");
  vsync();
  return;

  grid_init(5);
  grid_random_fill(grid_width * 4);
  renderer_render();

  // uint8_t i = 0;
  while(1) {
    vsync();

    // if (++i % 16 == 0)
    //   SCY_REG++;
    renderer_render();
  }
}
