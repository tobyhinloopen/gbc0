#pragma once

#include <stdint.h>
#include <stdbool.h>

#define grid_width 6

// The number of distinct normal tiles, usually 5 or 6
extern uint8_t grid_tile_id_count;

// The min-y coordinate of the playable grid, basically the ceiling.
// Game-Over if grid is raised when anything is touching the ceiling.
// This is also the ceiling of the interactable tiles. If min_y is greater than
// max_y, it loops over buffer_height.
//
// It is implemented as a pointer to buffer on x=0 y=grid_min_y
extern uint8_t *grid_min_y_ptr;

// The max-y coordinate of the playable grid, basically the floor of
// interactable tiles.
// If min_y is greater than max_y, it loops over buffer_height.
//
// It is implemented as a pointer to buffer on x=0 y=grid_max_y
extern uint8_t *grid_max_y_ptr;

// Clears the grid & set a tile id count.
void grid_init(uint8_t tile_id_count);

// Generates n random normal tiles from bottom to top, making sure no existing
// matches. Returns amount of blocks remaining, should be 0.
int grid_random_fill(uint8_t n);

// void grid_set(uint8_t i, uint8_t tile_id);
// void grid_set_xy(uint8_t x, uint8_t y, uint8_t tile_id);
// void grid_random_fill_row(uint8_t y);
// void grid_shift_pixel(void);
// void grid_shift_tile(void);
// void grid_last_row_fill(void);
