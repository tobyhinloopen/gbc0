#include "renderer.h"
#include <gb/gb.h>
#include <gb/cgb.h>

static uint8_t const block_tile_data[16] = {
  0x01,0xFF,0x1F,0x81,0x3F,0x81,0x7F,0x81,
  0x7F,0x81,0x7F,0x81,0x7F,0x81,0xFF,0xFF
};

// block_id 0 = empty (tile 0), block_id 1-6 = tile 1
uint8_t renderer_block_tiles[grid_max_block_types + 1] = {0, 1, 1, 1, 1, 1, 1};

// block_id 0 = palette 0, block_id 1-6 = palettes 0-5
uint8_t renderer_block_palettes[grid_max_block_types + 1] = {0, 0, 1, 2, 3, 4, 5};

void renderer_init(void) {
  set_bkg_data(1, 1, block_tile_data);
}

void renderer_render(void) {
  for (uint8_t y = grid_playable_min_y; y <= grid_playable_max_y; y++) {
    grid_row_t *row = &grid_rows[y];
    uint8_t screen_y = renderer_y + (grid_playable_max_y - y);

    VBK_REG = VBK_TILES;
    for (uint8_t x = 0; x < grid_width; x++) {
      uint8_t block_id = row->blocks[x];
      set_bkg_tile_xy(renderer_x + x, screen_y, renderer_block_tiles[block_id]);
    }

    VBK_REG = VBK_ATTRIBUTES;
    for (uint8_t x = 0; x < grid_width; x++) {
      uint8_t block_id = row->blocks[x];
      set_bkg_tile_xy(renderer_x + x, screen_y, renderer_block_palettes[block_id]);
    }
  }

  VBK_REG = VBK_TILES;
}
