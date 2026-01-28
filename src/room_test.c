#include "room_test.h"
#include "room.h"
#include "tiles.h"
#include "minunit.h"

static const uint8_t test_tiles[9] = {
  2,2,2,
  2,1,2,
  2,2,2,
};
static const room_t test_room = { 3, 3, test_tiles };

static char *test_room_get_tile(void) {
  mu_tests_run++;
  room_load(&test_room);
  mu_assert_eq(room_get_tile(0, 0), TILE_WALL, "%u");
  mu_assert_eq(room_get_tile(1, 1), TILE_FLOOR, "%u");
  mu_assert_eq(room_get_tile(5, 5), TILE_WALL, "%u"); // out of bounds
  return 0;
}

static char *test_room_walkable(void) {
  mu_tests_run++;
  room_load(&test_room);
  mu_assert(!room_is_walkable(0, 0)); // wall
  mu_assert(room_is_walkable(1, 1));  // floor
  mu_assert(!room_is_walkable(10, 10)); // out of bounds
  return 0;
}

char *room_test(void) {
  mu_run_test(test_room_get_tile);
  mu_run_test(test_room_walkable);
  return 0;
}
