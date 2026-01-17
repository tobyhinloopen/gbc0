#pragma once

#include <stdint.h>
#include <stdbool.h>

#define grid_width 6
#define grid_height 32
#define grid_playable_min_y 1
#define grid_playable_max_y 17

typedef struct {
  uint8_t blocks[grid_width];
  uint8_t flags0;
  uint8_t flags1;
} grid_row_t;

extern grid_row_t grid_rows[grid_height];
extern uint8_t grid_column_heights[grid_width];

// The number of distinct normal blocks, usually 5 or 6
extern uint8_t grid_block_id_count;

// Clears the grid & set a tile id count.
void grid_init(uint8_t block_id_count);

// Generates n random normal blocks from bottom to top, making sure no existing
// matches. Returns amount of blocks remaining, should be 0. Starts at playable
// area.
uint8_t grid_random_fill(uint8_t n);

// Count number of interactable blocks in playable area
uint8_t grid_count_playable_blocks(void);

// void grid_set(uint8_t i, uint8_t block_id);
// void grid_set_xy(uint8_t x, uint8_t y, uint8_t block_id);
// void grid_random_fill_row(uint8_t y);
// void grid_shift_pixel(void);
// void grid_shift_tile(void);
// void grid_last_row_fill(void);
