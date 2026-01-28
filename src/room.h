#pragma once

#include <stdint.h>
#include <stdbool.h>

#define ROOM_MAX_WIDTH  20
#define ROOM_MAX_HEIGHT 18

typedef struct {
  uint8_t width;
  uint8_t height;
  const uint8_t *tiles;
} room_t;

extern const room_t *current_room;

void room_load(const room_t *room);
uint8_t room_get_tile(uint8_t x, uint8_t y);
bool room_is_walkable(uint8_t x, uint8_t y);
