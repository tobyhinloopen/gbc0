#pragma once

#include <stdint.h>

#define GAME_STATE_TUTORIAL 0

extern uint8_t game_state;

void game_init(void);
void game_update(void);
