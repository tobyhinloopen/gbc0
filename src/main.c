#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include "block_tiles.h"
#include "grid.h"
#include "rand.h"
#include "grid_renderer.h"

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

const uint8_t tilemap[] = {
  1, 2, 3, 4, 5,
  6, 7, 8, 0, 1,
  2, 3, 4, 5, 6
};

void main(void) {
  puts("Hello world");

  DISPLAY_ON;
  SHOW_BKG;
  SHOW_WIN;

  WX_REG = 152 + 7;
  WY_REG = 0;

  if (_cpu == CGB_TYPE) {
    set_bkg_palette(0, 1, bg_palette0);
    set_bkg_palette(1, 1, bg_palette1);
  } else {
    BGP_REG = 0xE4;
  }

  rand_init();
  set_win_tile_xy(0, 0, 1);

  set_bkg_data(0, block_tiles_size, block_tiles);

  // Set the tilemap on background; 5x3 tile area starting at (0,1)
  set_bkg_tiles(0, 1, 5, 3, tilemap);

  uint8_t i = 0;

  grid_init(5);
  grid_random_fill(grid_width * 4);
  grid_renderer_render();

  while(1) {
    vsync();

    if (++i % 16 == 0)
      grid_shift_pixel();
    grid_renderer_render();
  }
}
