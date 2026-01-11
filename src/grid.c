#include "grid.h"
#include <string.h>
#include "rand.h"

uint8_t grid_tiles[grid_size];
uint8_t grid_column_heights[grid_width];

uint8_t grid_tile_id_count;
uint8_t grid_content_height;
uint8_t grid_tile_offset_y;

void grid_init(uint8_t tile_id_count) {
  memset(grid_tiles, 0, sizeof(grid_tiles));
  memset(grid_column_heights, 0, sizeof(grid_column_heights));
  grid_content_height = 0;
  grid_tile_id_count = tile_id_count;
  grid_tile_offset_y = 0;
}

void grid_random_fill(uint8_t c) {
  grid_random_fill_row(0);

  while(c--) {
    uint8_t rand_value = rand_next();
    uint8_t x = (rand_value >> 4) % grid_width;
    grid_set(x, grid_column_heights[x]++, 1 + (rand_value & 0x0F) % grid_tile_id_count);
  }
}

void grid_shift_pixel(void) {
  grid_tile_offset_y++;
  if (grid_tile_offset_y >= 8)
    grid_shift_tile();
}

void grid_shift_tile(void) {
  grid_tile_offset_y = 0;
  memmove(grid_tiles + grid_width, grid_tiles, grid_size - grid_width);

  for (uint8_t x = 0; x < grid_width; x++)
    grid_column_heights[x]++;

  grid_random_fill_row(0);
}

void grid_random_fill_row(uint8_t y) {
  for (uint8_t x = 0; x < grid_width; x += 2) {
    uint8_t rand_value = rand_next();
    grid_set(x, y, 1 + (rand_value & 0x0F) % grid_tile_id_count);
    grid_set(x + 1, y, 1 + (rand_value >> 4) % grid_tile_id_count);
  }
}

void grid_set(uint8_t x, uint8_t y, uint8_t tile_id) {
  grid_tiles[grid_index(x, y)] = tile_id;
}
