#include "game.h"
#include "tutorial.h"
#include "tiles.h"
#include "sprites.h"
#include <gb/gb.h>

uint8_t game_state;

void game_init(void) {
  tiles_init();
  SHOW_SPRITES;
  game_state = GAME_STATE_TUTORIAL;
  tutorial_init();
}

void game_update(void) {
  switch (game_state) {
    case GAME_STATE_TUTORIAL:
      tutorial_update();
      tutorial_render_hud();
      break;
  }
}
