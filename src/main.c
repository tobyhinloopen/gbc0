#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include "block_tiles.h"

const unsigned int bg_palette0[4] = {
  block_tiles_palette_0c0,
  block_tiles_palette_0c1,
  block_tiles_palette_0c2,
  block_tiles_palette_0c3
};

const unsigned int bg_palette1[4] = {
  block_tiles_palette_1c0,
  block_tiles_palette_1c1,
  block_tiles_palette_1c2,
  block_tiles_palette_1c3
};

const unsigned char tilemap[] = {
  1, 2, 3, 4, 5,
  6, 7, 8, 0, 1,
  2, 3, 4, 5, 6
};

void main(void) {
  puts("Hello world");

  DISPLAY_ON;
  SHOW_BKG;

  if (_cpu == CGB_TYPE) {
    set_bkg_palette(0, 1, bg_palette0);
    set_bkg_palette(1, 1, bg_palette1);
  } else {
    BGP_REG = 0xE4;
  }

  set_bkg_data(0, block_tiles_size, block_tiles);

  // Set the tilemap on background; 5x3 tile area starting at (0,1)
  set_bkg_tiles(0, 1, 5, 3, tilemap);

  uint8_t i = 0;

  while(1) {
    if (++i % 8 == 0)
      SCY_REG++;
    wait_vbl_done();
  }
}
