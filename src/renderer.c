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

// Circular tilemap state
static uint8_t tilemap_base;  // Tilemap row where grid row 0 is rendered
static uint8_t scroll_base;   // Added to grid_pixel_offset for SCY_REG

void renderer_init(void) {
  set_bkg_data(1, 1, block_tile_data);
  tilemap_base = renderer_y + grid_playable_max_y;  // = 18
  scroll_base = 0;
}

static void renderer_render_row(uint8_t grid_y) {
  grid_row_t *row = &grid_rows[grid_y];
  uint8_t screen_y = (tilemap_base - grid_y) & 31;

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

  VBK_REG = VBK_TILES;
}

void renderer_render(void) {
  if (grid_shifted) {
    grid_shifted = false;
    scroll_base += 8;
    tilemap_base = (tilemap_base + 1) & 31;
    renderer_render_row(0);
  }

  SCY_REG = grid_pixel_offset + scroll_base;
}

void renderer_render_all(void) {
  for (uint8_t y = 0; y <= grid_playable_max_y; y++)
    renderer_render_row(y);
}
