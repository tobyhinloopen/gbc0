#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include "block_tiles.h"
#include "grid.h"
#include "rand.h"
#include "grid_tilemap.h"

const uint16_t bg_palette0[4] = {
  block_tiles_palette_0c0,
  block_tiles_palette_0c1,
  block_tiles_palette_0c2,
  block_tiles_palette_0c3
};

const uint16_t bg_palette1[4] = {
  block_tiles_palette_1c0,
  block_tiles_palette_1c1,
  block_tiles_palette_1c2,
  block_tiles_palette_1c3
};

void main(void) {
  puts("Hello world");

  DISPLAY_ON;
  SHOW_BKG;
  SHOW_WIN;

  WX_REG = (uint8_t)(152 + 7);
  WY_REG = 0;

  if (_cpu == CGB_TYPE) {
    // TODO: Enable this, but disabled for now so performance issues show faster
    // cpu_fast();
    set_bkg_palette(0, 1, bg_palette0);
    set_bkg_palette(1, 1, bg_palette1);
  } else {
    BGP_REG = 0xE4;
  }

  rand_init();
  set_win_tile_xy(0, 0, 1);

  set_bkg_data(0, block_tiles_size, block_tiles);

  uint8_t i = 0;

  grid_init(5);
  grid_random_fill(grid_width * 4);
  grid_tilemap_render();

  while(1) {
    vsync();

    if (++i % 16 == 0)
      grid_shift_pixel();
    grid_tilemap_render();
    grid_last_row_fill();
  }
}
