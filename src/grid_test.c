#include "grid_test.h"
#include "minunit.h"

#include "grid.h"
#include "buffer.h"

static char *bench_grid_init(void) {
  grid_init(5);
  return 0;
}

static char *bench_grid_random_fill(void) {
  // assumes grid_init(x) was called!
  grid_random_fill(10);
  return 0;
}

static char *test_grid_init_clears_buffer(void) {
  grid_init(5);

  for (uint8_t *ptr = buffer_tiles; ptr < buffer_tiles_end; ptr++)
    if (*ptr)
      return "buffer not cleared";

  return 0;
}

static char *test_grid_random_fill(void) {
  uint8_t test_count = 18;
  uint8_t result = grid_random_fill(test_count);

  if (result) {
    char buffer[256];
    sprintf(buffer, "grid_random_fill A:\n exp. 0, got %hu\n", (uint8_t)result);
    return buffer;
  }

  uint8_t c = 0;
  for (uint8_t *ptr = buffer_tiles; ptr < buffer_tiles_end; ptr++)
    if (*ptr)
      c++;

  if (c != test_count) {
    char buffer[256];
    sprintf(buffer, "test_random_fill B:\n exp. %hu, got %hu\n", (uint8_t)test_count, (uint8_t)c);
    return buffer;
  }

  return 0;
}

char *grid_test(void) {
  mu_run_test(test_grid_init_clears_buffer);
  mu_run_test(test_grid_random_fill);

  mu_run_bench("g_init", bench_grid_init);
  mu_run_bench("g_random_fill", bench_grid_random_fill);

  return 0;
}
