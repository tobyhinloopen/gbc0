#include "tutorial.h"
#include "actor.h"
#include "room.h"
#include "player.h"
#include "sprites.h"
#include "tiles.h"
#include "font_stdio.h"
#include <gb/gb.h>

uint8_t tutorial_current_test;
uint8_t tutorial_result;
uint16_t tutorial_timer;

// Item IDs
#define ITEM_NONE        0
#define ITEM_SCREWDRIVER 1

// Room data for TEST 001: empty 10x9 room
static const uint8_t room_001_tiles[10 * 9] = {
  2,2,2,2,2,2,2,2,2,2,
  2,1,1,1,1,1,1,1,1,2,
  2,1,1,1,1,1,1,1,1,2,
  2,1,1,1,1,1,1,1,1,2,
  2,1,1,1,1,1,1,1,1,2,
  2,1,1,1,1,1,1,1,1,2,
  2,1,1,1,1,1,1,1,1,2,
  2,1,1,1,1,1,1,1,4,2,
  2,2,2,2,2,2,2,2,2,2,
};

static const room_t room_001 = { 10, 9, room_001_tiles };

// Room data for TEST 002: wall between player and target
static const uint8_t room_002_tiles[10 * 9] = {
  2,2,2,2,2,2,2,2,2,2,
  2,1,1,1,2,1,1,1,1,2,
  2,1,1,1,2,1,1,1,1,2,
  2,1,1,1,2,1,1,1,1,2,
  2,1,1,1,2,1,1,1,1,2,
  2,1,1,1,1,1,1,1,1,2,
  2,1,1,1,1,1,1,1,1,2,
  2,1,1,1,1,1,1,1,4,2,
  2,2,2,2,2,2,2,2,2,2,
};

static const room_t room_002 = { 10, 9, room_002_tiles };

// Room data for TEST 030: table with screwdriver, screw nearby
static const uint8_t room_030_tiles[10 * 9] = {
  2,2,2,2,2,2,2,2,2,2,
  2,1,1,1,1,1,1,1,1,2,
  2,1,1,1,1,1,1,1,1,2,
  2,1,1,3,3,1,1,1,1,2,
  2,1,1,1,1,1,1,1,1,2,
  2,1,1,1,1,1,5,1,1,2,
  2,1,1,1,1,1,1,1,1,2,
  2,1,1,1,1,1,1,1,1,2,
  2,2,2,2,2,2,2,2,2,2,
};

static const room_t room_030 = { 10, 9, room_030_tiles };

// Actor IDs for TEST 030
static uint8_t screwdriver_actor_id;
static bool screw_used;

// Target tile position
static uint8_t target_x, target_y;

static void setup_test_001(void) {
  actor_clear();
  room_load(&room_001);
  uint8_t pid = actor_spawn(1, 1, ACTOR_TYPE_PLAYER, SPRITE_PLAYER_DOWN);
  player_init(pid);
  target_x = 8;
  target_y = 7;
}

static void setup_test_002(void) {
  actor_clear();
  room_load(&room_002);
  uint8_t pid = actor_spawn(1, 1, ACTOR_TYPE_PLAYER, SPRITE_PLAYER_DOWN);
  player_init(pid);
  target_x = 8;
  target_y = 7;
}

static void setup_test_030(void) {
  actor_clear();
  room_load(&room_030);
  uint8_t pid = actor_spawn(1, 1, ACTOR_TYPE_PLAYER, SPRITE_PLAYER_DOWN);
  player_init(pid);
  // Screwdriver on table — actor placed adjacent to table so player can pick it up
  screwdriver_actor_id = actor_spawn(3, 4, ACTOR_TYPE_OBJECT, SPRITE_SCREWDRIVER);
  actors[screwdriver_actor_id].item_id = ITEM_SCREWDRIVER;
  screw_used = false;
  target_x = 3;
  target_y = 4;
}

static void setup_current_test(void) {
  tutorial_timer = TUTORIAL_TIMER_FRAMES;
  tutorial_result = TUTORIAL_RUNNING;

  switch (tutorial_current_test) {
    case TEST_001: setup_test_001(); break;
    case TEST_002: setup_test_002(); break;
    case TEST_030: setup_test_030(); break;
  }
}

static bool check_test_001(void) {
  actor_t *p = &actors[player_actor_id];
  return (p->x == target_x && p->y == target_y);
}

static bool check_test_002(void) {
  actor_t *p = &actors[player_actor_id];
  return (p->x == target_x && p->y == target_y);
}

static bool check_test_030(void) {
  if (player_interact_pressed) {
    uint8_t fx, fy;
    actor_get_facing_tile(player_actor_id, &fx, &fy);

    if (player_held_item == ITEM_NONE) {
      // Try to pick up screwdriver
      actor_t *target = actor_at(fx, fy);
      if (target != NULL && target->item_id == ITEM_SCREWDRIVER) {
        player_held_item = ITEM_SCREWDRIVER;
        target->type = ACTOR_TYPE_NONE; // Remove from world
        // Update target highlight to screw
        target_x = 6;
        target_y = 5;
      }
    } else if (player_held_item == ITEM_SCREWDRIVER) {
      // Try to use on screw tile
      uint8_t tile = room_get_tile(fx, fy);
      if (tile == TILE_SCREW) {
        screw_used = true;
        player_held_item = ITEM_NONE;
      }
    }
  }
  return screw_used;
}

// Frame counter for target blink
static uint8_t blink_counter;

void tutorial_init(void) {
  tutorial_current_test = TEST_001;
  blink_counter = 0;
  setup_current_test();
}

void tutorial_update(void) {
  if (tutorial_result == TUTORIAL_PASS || tutorial_result == TUTORIAL_DONE)
    return;

  if (tutorial_result == TUTORIAL_FAIL) {
    // Wait for A to retry
    if (joypad() & J_A) {
      while (joypad() & J_A) vsync();
      setup_current_test();
    }
    return;
  }

  // Timer
  if (tutorial_timer > 0) {
    tutorial_timer--;
  } else {
    tutorial_result = TUTORIAL_FAIL;
    return;
  }

  player_update();

  // Blink target tile
  blink_counter++;
  if (tutorial_current_test != TEST_030 || player_held_item == ITEM_NONE) {
    // Show/hide target marker via tilemap
    if (blink_counter & 0x10)
      set_bkg_tile_xy(target_x, target_y, TILE_TARGET);
    else {
      uint8_t orig = current_room->tiles[target_y * current_room->width + target_x];
      set_bkg_tile_xy(target_x, target_y, orig);
    }
  } else {
    // Blink screw target
    if (blink_counter & 0x10)
      set_bkg_tile_xy(target_x, target_y, TILE_TARGET);
    else
      set_bkg_tile_xy(target_x, target_y, TILE_SCREW);
  }

  sprites_update();

  // Check win condition
  bool passed = false;
  switch (tutorial_current_test) {
    case TEST_001: passed = check_test_001(); break;
    case TEST_002: passed = check_test_002(); break;
    case TEST_030: passed = check_test_030(); break;
  }

  if (passed) {
    tutorial_result = TUTORIAL_PASS;
    tutorial_current_test++;
    if (tutorial_current_test >= TEST_COUNT) {
      tutorial_result = TUTORIAL_DONE;
    } else {
      // Brief pause then load next test
      for (uint8_t i = 0; i < 60; i++) vsync();
      setup_current_test();
    }
  }
}

void tutorial_render_hud(void) {
  // Position cursor at top for HUD overlay
  font_cursor_x = 0;
  font_cursor_y = 0;

  uint16_t seconds_left = (tutorial_timer + 59) / 60;

  switch (tutorial_current_test) {
    case TEST_001: font_printf("TEST 001 - MOVES  %u", seconds_left); break;
    case TEST_002: font_printf("TEST 002 - NAVIGATE  %u", seconds_left); break;
    case TEST_030: font_printf("TEST 030 - TOOLS  %u", seconds_left); break;
  }

  if (tutorial_result == TUTORIAL_FAIL) {
    font_cursor_x = 0;
    font_cursor_y = 40;
    font_printf("FAIL - Press A");
  } else if (tutorial_result == TUTORIAL_DONE) {
    font_cursor_x = 0;
    font_cursor_y = 40;
    font_printf("ALL TESTS PASSED");
  }
}
