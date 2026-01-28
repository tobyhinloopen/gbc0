#include "actor.h"
#include "room.h"
#include <stddef.h>

actor_t actors[ACTOR_MAX];
uint8_t actor_count;

void actor_clear(void) {
  actor_count = 0;
  for (uint8_t i = 0; i < ACTOR_MAX; i++)
    actors[i].type = ACTOR_TYPE_NONE;
}

uint8_t actor_spawn(uint8_t x, uint8_t y, uint8_t type, uint8_t sprite_id) {
  uint8_t id = actor_count++;
  actors[id].x = x;
  actors[id].y = y;
  actors[id].pixel_ox = 0;
  actors[id].pixel_oy = 0;
  actors[id].direction = DIR_DOWN;
  actors[id].sprite_id = sprite_id;
  actors[id].type = type;
  actors[id].item_id = 0;
  return id;
}

bool actor_move(uint8_t id, int8_t dx, int8_t dy) {
  uint8_t nx = actors[id].x + dx;
  uint8_t ny = actors[id].y + dy;
  if (!room_is_walkable(nx, ny))
    return false;
  if (actor_at(nx, ny) != NULL)
    return false;
  actors[id].pixel_ox = -dx * 8;
  actors[id].pixel_oy = -dy * 8;
  actors[id].x = nx;
  actors[id].y = ny;
  return true;
}

void actor_face(uint8_t id, uint8_t direction) {
  actors[id].direction = direction;
}

void actor_get_facing_tile(uint8_t id, uint8_t *out_x, uint8_t *out_y) {
  actor_t *a = &actors[id];
  *out_x = a->x;
  *out_y = a->y;
  switch (a->direction) {
    case DIR_DOWN:  (*out_y)++; break;
    case DIR_UP:    (*out_y)--; break;
    case DIR_LEFT:  (*out_x)--; break;
    case DIR_RIGHT: (*out_x)++; break;
  }
}

actor_t *actor_at(uint8_t x, uint8_t y) {
  for (uint8_t i = 0; i < actor_count; i++) {
    if (actors[i].type != ACTOR_TYPE_NONE && actors[i].x == x && actors[i].y == y)
      return &actors[i];
  }
  return NULL;
}
