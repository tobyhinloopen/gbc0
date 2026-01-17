#include "grid.h"
#include <string.h>
#include "rand.h"
#include <assert.h>

grid_row_t grid_rows[grid_height];
uint8_t grid_column_heights[grid_width];
uint8_t grid_block_id_count = 0;

void grid_init(uint8_t block_id_count) {
  assert(block_id_count == 5 || block_id_count == 6);
  grid_block_id_count = block_id_count;
  memset(grid_rows, 0, sizeof(grid_rows));
  memset(grid_column_heights, 0, sizeof(grid_column_heights));
}

void grid_random_fill_row(uint8_t r) {

}

uint8_t grid_random_fill(uint8_t c) {
  for(; c > 0; c--) {
    uint8_t rand_value = rand_next();
    uint8_t x = (rand_value >> 4) % grid_width;
    uint8_t block_id = 1 + (rand_value & 0x0F) % grid_block_id_count;
    uint8_t *grid_column_height = &grid_column_heights[x];
    if (*grid_column_height == 0)
      (*grid_column_height)++;
    uint8_t y = (*grid_column_height)++;
    if (y > grid_playable_max_y)
      return c;
    grid_rows[y].blocks[x] = block_id;
  }

  return 0;
}

uint8_t grid_count_playable_blocks(void) {
  uint8_t c = 0;

  for (uint8_t y = grid_playable_min_y; y <= grid_playable_max_y; y++) {
    grid_row_t *row = &grid_rows[y];
    for (uint8_t x = 0; x < grid_width; x++)
      if (row->blocks[x])
        c++;
  }

  return c;
}
