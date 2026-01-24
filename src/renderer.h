#pragma once

#include "grid.h"

#define renderer_x 0
#define renderer_y grid_playable_min_y

// Tile index for each block_id (0 = empty, 1+ = block types)
extern uint8_t renderer_block_tiles[grid_max_block_types + 1];

// Palette index for each block_id (0-7)
extern uint8_t renderer_block_palettes[grid_max_block_types + 1];

// Initialize renderer - loads tile data into VRAM
void renderer_init(void);

// Render the grid to the screen (lightweight - only updates on shift)
void renderer_render(void);

// Full render of all grid rows (call once at startup)
void renderer_render_all(void);
