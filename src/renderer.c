#include "renderer.h"
#include <gb/gb.h>
#include <gb/cgb.h>

uint8_t const renderer_tile[16] = {
  0x01,0xFF,0x1F,0x81,0x3F,0x81,0x7F,0x81,
  0x7F,0x81,0x7F,0x81,0x7F,0x81,0xFF,0xFF
};

void renderer_render(void) {
  // SCY_REG = 0; // grid_tile_pixel_offset_y - grid_pixel_height;

  // set_bkg_blocks(renderer_x, renderer_y, buffer_width, buffer_height, buffer_blocks);
}
