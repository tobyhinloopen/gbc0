#include "grid_tilemap.h"
#include "grid.h"

#include <gb/gb.h>
#include <gb/cgb.h>

void grid_tilemap_render(void) {
  SCY_REG = grid_tile_pixel_offset_y - grid_pixel_height;

  set_bkg_tiles(grid_tilemap_x, grid_tilemap_y, grid_width, grid_height, grid_tiles);
}
