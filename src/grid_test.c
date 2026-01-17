#include "grid_test.h"
#include "minunit.h"

#include "grid.h"

static char *bench_grid_init(void) {
  grid_init(5);
  return 0;
}

static char *bench_grid_random_fill(void) {
  grid_random_fill(10);
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

char *grid_test(void) {
  mu_run_test(test_grid_init);
  mu_run_test(test_grid_random_fill);

  mu_run_bench("grid_init", bench_grid_init);
  mu_run_bench("grid_random_fill", bench_grid_random_fill);

  return 0;
}
