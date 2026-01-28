#include "actor_test.h"
#include "actor.h"
#include "room.h"
#include "tiles.h"
#include "minunit.h"

// Simple test room: 5x5, floor surrounded by walls
static const uint8_t test_room_tiles[25] = {
  2,2,2,2,2,
  2,1,1,1,2,
  2,1,1,1,2,
  2,1,1,1,2,
  2,2,2,2,2,
};
static const room_t test_room = { 5, 5, test_room_tiles };

static void setup(void) {
  actor_clear();
  room_load(&test_room);
}

static char *test_actor_spawn(void) {
  mu_tests_run++;
  setup();
  uint8_t id = actor_spawn(1, 1, ACTOR_TYPE_PLAYER, 0);
  mu_assert_eq(id, 0, "%u");
  mu_assert_eq(actors[0].x, 1, "%u");
  mu_assert_eq(actors[0].y, 1, "%u");
  mu_assert_eq(actors[0].type, ACTOR_TYPE_PLAYER, "%u");
  mu_assert_eq(actor_count, 1, "%u");
  return 0;
}

static char *test_actor_move(void) {
  mu_tests_run++;
  setup();
  actor_spawn(2, 2, ACTOR_TYPE_PLAYER, 0);
  mu_assert(actor_move(0, 1, 0));  // move right to (3,2) - floor
  mu_assert_eq(actors[0].x, 3, "%u");
  mu_assert(!actor_move(0, 1, 0)); // move right to (4,2) - wall
  mu_assert_eq(actors[0].x, 3, "%u");
  return 0;
}

static char *test_actor_collision(void) {
  mu_tests_run++;
  setup();
  actor_spawn(1, 1, ACTOR_TYPE_PLAYER, 0);
  actor_spawn(2, 1, ACTOR_TYPE_OBJECT, 0);
  mu_assert(!actor_move(0, 1, 0)); // blocked by other actor
  mu_assert_eq(actors[0].x, 1, "%u");
  return 0;
}

static char *test_actor_facing(void) {
  mu_tests_run++;
  setup();
  actor_spawn(2, 2, ACTOR_TYPE_PLAYER, 0);
  actor_face(0, DIR_RIGHT);
  uint8_t fx, fy;
  actor_get_facing_tile(0, &fx, &fy);
  mu_assert_eq(fx, 3, "%u");
  mu_assert_eq(fy, 2, "%u");
  return 0;
}

char *actor_test(void) {
  mu_run_test(test_actor_spawn);
  mu_run_test(test_actor_move);
  mu_run_test(test_actor_collision);
  mu_run_test(test_actor_facing);
  return 0;
}
