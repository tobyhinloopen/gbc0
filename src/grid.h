#pragma once

#include <stdint.h>

#define grid_width 6
#define grid_height 13
#define grid_size (grid_width * grid_height)

#define grid_index(x, y) ((y) * grid_width + (x))

extern uint8_t grid_tile_id_count;
extern uint8_t grid_tiles[grid_size];
extern uint8_t grid_column_heights[grid_width];
extern uint8_t grid_content_height;
extern uint8_t grid_tile_offset_y;

void grid_init(uint8_t id_count);
void grid_random_fill(uint8_t c);
void grid_set(uint8_t x, uint8_t y, uint8_t tile_id);
void grid_random_fill_row(uint8_t y);
void grid_shift_pixel(void);
void grid_shift_tile(void);
