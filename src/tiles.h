#pragma once

#include <stdint.h>

// Tile indices in VRAM bank 0 (BG tiles)
#define TILE_FLOOR    1
#define TILE_WALL     2
#define TILE_TABLE    3
#define TILE_TARGET   4
#define TILE_SCREW    5

// Number of BG tiles to load
#define TILES_BG_COUNT 5

// Sprite tile indices (in OBJ VRAM)
#define SPRITE_PLAYER_DOWN   0
#define SPRITE_PLAYER_UP     1
#define SPRITE_PLAYER_LEFT   2
#define SPRITE_PLAYER_RIGHT  3
#define SPRITE_SCREWDRIVER   4

#define TILES_SPRITE_COUNT 5

extern const uint8_t tiles_bg_data[];
extern const uint8_t tiles_sprite_data[];

// Load BG and sprite tile data into VRAM
void tiles_init(void);
