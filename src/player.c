#include "player.h"
#include "actor.h"
#include <gb/gb.h>

uint8_t player_actor_id;
uint8_t player_held_item;
bool player_interact_pressed;
bool player_drop_pressed;

static uint8_t move_cooldown;
static uint8_t prev_keys;

void player_init(uint8_t actor_id) {
  player_actor_id = actor_id;
  player_held_item = 0;
  player_interact_pressed = false;
  player_drop_pressed = false;
  move_cooldown = 0;
  prev_keys = 0;
}

void player_update(void) {
  uint8_t keys = joypad();
  player_interact_pressed = false;
  player_drop_pressed = false;

  // A button: interact (edge-triggered)
  if ((keys & J_A) && !(prev_keys & J_A))
    player_interact_pressed = true;

  // B button: drop (edge-triggered)
  if ((keys & J_B) && !(prev_keys & J_B))
    player_drop_pressed = true;

  prev_keys = keys;

  if (move_cooldown > 0) {
    move_cooldown--;
    // Lerp pixel offset toward 0
    actor_t *p = &actors[player_actor_id];
    if (p->pixel_ox > 0) p->pixel_ox--;
    else if (p->pixel_ox < 0) p->pixel_ox++;
    if (p->pixel_oy > 0) p->pixel_oy--;
    else if (p->pixel_oy < 0) p->pixel_oy++;
    return;
  }

  int8_t dx = 0, dy = 0;
  uint8_t dir = actors[player_actor_id].direction;

  if (keys & J_DOWN) { dy = 1; dir = DIR_DOWN; }
  else if (keys & J_UP) { dy = -1; dir = DIR_UP; }
  else if (keys & J_LEFT) { dx = -1; dir = DIR_LEFT; }
  else if (keys & J_RIGHT) { dx = 1; dir = DIR_RIGHT; }

  if (dx != 0 || dy != 0) {
    actor_face(player_actor_id, dir);
    if (actor_move(player_actor_id, dx, dy))
      move_cooldown = PLAYER_MOVE_COOLDOWN;
  }
}
