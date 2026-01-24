#include "grid_test.h"
#include "minunit.h"

#include "grid.h"

static char *bench_grid_init(void) {
  grid_init(5);
  return 0;
}

static char *bench_grid_random_fill(void) {
  grid_random_fill(9);
  return 0;
}

static char *test_grid_init(void) {
  grid_init(5);

  mu_assert_eq(grid_block_id_count, 5, "%u");

  for (uint8_t x=0; x<grid_width; x++)
    mu_assert_eq(grid_column_heights[x], 0, "%u");

  uint8_t block_count = grid_count_playable_blocks();
  mu_assert_eq(block_count, 0, "%u");

  return 0;
}

static char *test_grid_random_fill(void) {
  uint8_t test_count = 18;
  uint8_t result = grid_random_fill(test_count);

  mu_assert_eq(result, 0, "%u");

  uint8_t block_count = grid_count_playable_blocks();
  mu_assert_eq(block_count, test_count, "%u");

  return 0;
}

static char *test_grid_random_fill_row(void) {
  grid_init(5);

  // Row 0 should be empty
  for (uint8_t x = 0; x < grid_width; x++)
    mu_assert_eq(grid_rows[0].blocks[x], 0, "%u");

  grid_random_fill_row(0);

  // Row 0 should now have blocks in all columns
  for (uint8_t x = 0; x < grid_width; x++) {
    mu_assert(grid_rows[0].blocks[x] >= 1);
    mu_assert(grid_rows[0].blocks[x] <= grid_block_id_count);
  }

  return 0;
}

static char *test_grid_raise_pixel(void) {
  grid_init(5);
  mu_assert_eq(grid_pixel_offset, 0, "%u");

  // Raise 7 times - should not shift yet
  for (uint8_t i = 0; i < 7; i++)
    grid_raise_pixel();
  mu_assert_eq(grid_pixel_offset, 7, "%u");

  // Place a marker block at row 1
  grid_rows[1].blocks[0] = 3;

  // Raise once more - should wrap and shift
  grid_raise_pixel();
  mu_assert_eq(grid_pixel_offset, 0, "%u");

  // Marker should have moved to row 2
  mu_assert_eq(grid_rows[2].blocks[0], 3, "%u");

  // Row 0 should have new blocks
  for (uint8_t x = 0; x < grid_width; x++)
    mu_assert(grid_rows[0].blocks[x] >= 1);

  return 0;
}

char *grid_test(void) {
  mu_run_test(test_grid_init);
  mu_run_test(test_grid_random_fill);
  mu_run_test(test_grid_random_fill_row);
  mu_run_test(test_grid_raise_pixel);

  mu_run_bench("grid_init", bench_grid_init);
  mu_run_bench("grid_random_fill", bench_grid_random_fill);

  return 0;
}
