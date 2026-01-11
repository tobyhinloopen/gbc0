#include "grid_renderer.h"
#include "grid.h"

#include <gb/gb.h>
#include <gb/cgb.h>

void grid_renderer_render(void) {
  uint8_t sy = 18;
  uint8_t *ptr = grid_tiles;
  uint8_t *ptr_max = grid_tiles + grid_size;

  SCY_REG = grid_tile_offset_y;

  while (ptr < ptr_max && sy > 0) {
    set_bkg_tiles(grid_renderer_x, sy, grid_width, 1, ptr);
    ptr += grid_width;
    sy--;
  }
}
