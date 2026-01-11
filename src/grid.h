#pragma once

#include <stdint.h>
#include <stdbool.h>

#define grid_width 6
#define grid_height 20
#define grid_size (grid_width * grid_height)
#define grid_max_y (grid_height - 1)
#define grid_pixel_height 8

#define grid_index(x, y) ((y) * grid_width + (x))

extern uint8_t grid_tile_id_count;
extern uint8_t grid_tiles[grid_size];
extern uint8_t grid_col_min_y[grid_width];
extern uint8_t grid_min_y;
extern uint8_t grid_tile_pixel_offset_y;
extern bool grid_last_row_fill_required;

void grid_init(uint8_t id_count);
void grid_random_fill(uint8_t c);
void grid_set(uint8_t i, uint8_t tile_id);
void grid_set_xy(uint8_t x, uint8_t y, uint8_t tile_id);
void grid_random_fill_row(uint8_t y);
void grid_shift_pixel(void);
void grid_shift_tile(void);
void grid_last_row_fill(void);
