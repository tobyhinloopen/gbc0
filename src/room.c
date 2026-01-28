#include "room.h"
#include "tiles.h"
#include <gb/gb.h>
#include <gb/cgb.h>

const room_t *current_room;

void room_load(const room_t *room) {
  current_room = room;

  // Clear tilemap
  for (uint8_t y = 0; y < 18; y++)
    for (uint8_t x = 0; x < 20; x++)
      set_bkg_tile_xy(x, y, 0);

  // Write room tiles to BG tilemap
  for (uint8_t y = 0; y < room->height; y++) {
    for (uint8_t x = 0; x < room->width; x++) {
      uint8_t tile = room->tiles[y * room->width + x];
      set_bkg_tile_xy(x, y, tile);
    }
  }

  // Set palette attributes for CGB
  VBK_REG = VBK_ATTRIBUTES;
  for (uint8_t y = 0; y < room->height; y++) {
    for (uint8_t x = 0; x < room->width; x++) {
      uint8_t tile = room->tiles[y * room->width + x];
      uint8_t pal = 0;
      if (tile == TILE_WALL) pal = 1;
      else if (tile == TILE_TARGET) pal = 2;
      else if (tile == TILE_TABLE) pal = 3;
      else if (tile == TILE_SCREW) pal = 4;
      set_bkg_tile_xy(x, y, pal);
    }
  }
  VBK_REG = VBK_TILES;
}

uint8_t room_get_tile(uint8_t x, uint8_t y) {
  if (current_room == NULL) return 0;
  if (x >= current_room->width || y >= current_room->height) return TILE_WALL;
  return current_room->tiles[y * current_room->width + x];
}

bool room_is_walkable(uint8_t x, uint8_t y) {
  uint8_t tile = room_get_tile(x, y);
  return tile == TILE_FLOOR || tile == TILE_TARGET;
}
