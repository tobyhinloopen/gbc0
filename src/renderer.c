#include "renderer.h"
#include "buffer.h"

#include <gb/gb.h>
#include <gb/cgb.h>

void renderer_render(void) {
  SCY_REG = 0; // grid_tile_pixel_offset_y - grid_pixel_height;

  set_bkg_tiles(grid_tilemap_x, grid_tilemap_y, buffer_width, buffer_height, buffer_tiles);
}
