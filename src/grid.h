#pragma once

#include <stdint.h>
#include <stdbool.h>

#define grid_width 6
#define grid_height 32
#define grid_playable_min_y 1
#define grid_playable_max_y 17
#define grid_max_block_types 6

typedef struct {
  uint8_t blocks[grid_width];
  uint8_t flags0;
  uint8_t flags1;
} grid_row_t;

extern grid_row_t grid_rows[grid_height];
extern uint8_t grid_column_heights[grid_width];

// The number of distinct normal blocks (5 to grid_max_block_types)
extern uint8_t grid_block_id_count;

// Current pixel offset within tile (0-7)
extern uint8_t grid_pixel_offset;

// Set to true when a tile shift occurs (renderer should clear after handling)
extern bool grid_shifted;

// Clears the grid & set a tile id count.
void grid_init(uint8_t block_id_count);

// Generates n random normal blocks from bottom to top, making sure no existing
// matches. Returns amount of blocks remaining, should be 0. Starts at playable
// area.
uint8_t grid_random_fill(uint8_t n);

// Count number of interactable blocks in playable area
uint8_t grid_count_playable_blocks(void);

// Raise the grid by 1 pixel
void grid_raise_pixel(void);

// Fill row y with random blocks
void grid_random_fill_row(uint8_t y);

// void grid_set(uint8_t i, uint8_t block_id);
// void grid_set_xy(uint8_t x, uint8_t y, uint8_t block_id);
