#pragma once

#include <stdint.h>
#include <stdbool.h>

#define ACTOR_MAX 16

#define DIR_DOWN  0
#define DIR_UP    1
#define DIR_LEFT  2
#define DIR_RIGHT 3

#define ACTOR_TYPE_NONE    0
#define ACTOR_TYPE_PLAYER  1
#define ACTOR_TYPE_HUMAN   2
#define ACTOR_TYPE_OBJECT  3

typedef struct {
  uint8_t x;
  uint8_t y;
  int8_t pixel_ox;  // pixel offset from tile pos (-8..8), for smooth movement
  int8_t pixel_oy;
  uint8_t direction;
  uint8_t sprite_id;
  uint8_t type;
  uint8_t item_id;  // for objects: what item this is; for player: held item
} actor_t;

extern actor_t actors[ACTOR_MAX];
extern uint8_t actor_count;

void actor_clear(void);
uint8_t actor_spawn(uint8_t x, uint8_t y, uint8_t type, uint8_t sprite_id);
bool actor_move(uint8_t id, int8_t dx, int8_t dy);
void actor_face(uint8_t id, uint8_t direction);
void actor_get_facing_tile(uint8_t id, uint8_t *out_x, uint8_t *out_y);
actor_t *actor_at(uint8_t x, uint8_t y);
