#include "sprites.h"
#include "actor.h"
#include "tiles.h"
#include <gb/gb.h>

void sprites_update(void) {
  uint8_t oam = 0;
  for (uint8_t i = 0; i < actor_count && oam < 40; i++) {
    if (actors[i].type == ACTOR_TYPE_NONE) continue;

    uint8_t sprite_tile = actors[i].sprite_id;
    // Player uses directional sprites
    if (actors[i].type == ACTOR_TYPE_PLAYER)
      sprite_tile = actors[i].direction; // DIR_DOWN=0 matches SPRITE_PLAYER_DOWN=0

    move_sprite(oam, (actors[i].x * 8) + 8 + actors[i].pixel_ox,
                     (actors[i].y * 8) + 16 + actors[i].pixel_oy);
    set_sprite_tile(oam, sprite_tile);
    oam++;
  }
  // Hide remaining sprites
  for (; oam < 40; oam++)
    move_sprite(oam, 0, 0);
}

void sprites_hide_all(void) {
  for (uint8_t i = 0; i < 40; i++)
    move_sprite(i, 0, 0);
}
