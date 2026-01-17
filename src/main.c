#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include "grid.h"
#include "rand.h"
#include "renderer.h"
#include "test.h"

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

  if (test_main()) {
    vsync();
    return;
  }

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
