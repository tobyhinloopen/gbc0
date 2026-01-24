#include <gb/gb.h>
#include <gb/cgb.h>
#include "font_stdio.h"
#include "grid.h"
#include "rand.h"
#include "renderer.h"
#include "test.h"

// Block palettes: white bg, colored fg, dark, darker
const uint16_t block_palettes[grid_max_block_types][4] = {
  { 0x7FFF, 0x001F, 0x0015, 0x000A },  // Red
  { 0x7FFF, 0x03E0, 0x02A0, 0x0140 },  // Green
  { 0x7FFF, 0x7C00, 0x5000, 0x2800 },  // Blue
  { 0x7FFF, 0x03FF, 0x02B5, 0x014A },  // Yellow
  { 0x7FFF, 0x7C1F, 0x5015, 0x280A },  // Purple
  { 0x7FFF, 0x7FE0, 0x52A0, 0x2940 },  // Cyan
};

void main(void) {
  DISPLAY_ON;
  SHOW_BKG;
  // SHOW_WIN;

  // WX_REG = (uint8_t)(152 + 7);
  // WY_REG = 0;

  if (_cpu == CGB_TYPE) {
    for (uint8_t i = 0; i < grid_max_block_types; i++)
      set_bkg_palette(i, 1, block_palettes[i]);
  } else {
    BGP_REG = 0xE4;
  }

  rand_init();
  renderer_init();

  if (test_main()) {
    vsync();
    return;
  }
  vsync();

  font_printf("Press A to continue.\n");

  while (!(joypad() & J_A))
    vsync();
  while (joypad() & J_A)
    vsync();

  grid_init(5);
  grid_random_fill(grid_width * 4);
  renderer_render();

  uint8_t i = 0;
  while(1) {
    vsync();

    if (++i % 16 == 0)
      SCY_REG++;
    renderer_render();
  }
}
