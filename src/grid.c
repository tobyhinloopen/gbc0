#include "grid.h"
#include <string.h>
#include "rand.h"

// TODO: Change to a circular buffer so `grid_shift_tile` doesn't involve
// shifting all tiles AND a complete re-render of all tiles every shift isn't
// required.
uint8_t grid_tiles[grid_size];
uint8_t grid_col_min_y[grid_width];
uint8_t grid_tile_id_count;
uint8_t grid_min_y;
uint8_t grid_tile_pixel_offset_y;
bool grid_last_row_fill_required;

void grid_init(uint8_t tile_id_count) {
  memset(grid_tiles, 0, sizeof(grid_tiles));
  memset(grid_col_min_y, grid_max_y, sizeof(grid_col_min_y));
  grid_tile_id_count = tile_id_count;
  grid_min_y = 0;
  grid_tile_pixel_offset_y = 0;
  grid_last_row_fill_required = false;
}

void grid_random_fill(uint8_t c) {
  grid_last_row_fill_required = true;

  while(c--) {
    uint8_t rand_value = rand_next();
    uint8_t x = (rand_value >> 4) % grid_width;
    uint8_t y = grid_col_min_y[x]--;
    grid_set_xy(x, y, 1 + (rand_value & 0x0F) % grid_tile_id_count);
    if (y < grid_min_y)
      grid_min_y = y;
  }
}

void grid_shift_pixel(void) {
  grid_tile_pixel_offset_y++;
  if (grid_tile_pixel_offset_y >= grid_pixel_height)
    grid_shift_tile();
}

void grid_shift_tile(void) {
  grid_tile_pixel_offset_y = 0;

  uint8_t * src = grid_tiles + grid_width;
  uint8_t * dst = grid_tiles;

  for (uint8_t row = 0; row < grid_height - 1; row++) {
    *(dst++) = *(src++);
    *(dst++) = *(src++);
    *(dst++) = *(src++);
    *(dst++) = *(src++);
    *(dst++) = *(src++);
    *(dst++) = *(src++);
  }

  for (uint8_t x = 0; x < grid_width; x++)
    grid_col_min_y[x]--;

  grid_last_row_fill_required = true;
}

void grid_last_row_fill(void) {
  if (!grid_last_row_fill_required) return;
  grid_random_fill_row(grid_max_y);
  grid_last_row_fill_required = false;
}

void grid_random_fill_row(uint8_t y) {
  uint8_t i = grid_index(0, y);
  for (uint8_t x = 0; x < grid_width; x += 2) {
    uint8_t rand_value = rand_next();
    grid_set(i++, 1 + (rand_value & 0x0F) % grid_tile_id_count);
    grid_set(i++, 1 + (rand_value >> 4) % grid_tile_id_count);
  }
}

void grid_set(uint8_t i, uint8_t tile_id) {
  grid_tiles[i] = tile_id;
}

void grid_set_xy(uint8_t x, uint8_t y, uint8_t tile_id) {
  grid_set(grid_index(x, y), tile_id);
}
