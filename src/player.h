#pragma once

#include <stdint.h>
#include <stdbool.h>

#define PLAYER_MOVE_COOLDOWN 8

extern uint8_t player_actor_id;
extern uint8_t player_held_item;
extern bool player_interact_pressed;
extern bool player_drop_pressed;

void player_init(uint8_t actor_id);
void player_update(void);
