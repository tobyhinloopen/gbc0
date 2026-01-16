#include "test.h"

#include <stdio.h>

#include "grid_test.h"
#include "rand_test.h"

int tests_run = 0;

char *all_tests(void) {
  mu_run_suite(grid_test);
  mu_run_suite(rand_test);

  return 0;
}

int test_main(void) {
  char *result = all_tests();
  if (result != 0) {
    printf("%s\n", result);
  } else {
    printf("ALL TESTS PASSED\n");
  }
  printf("Tests run: %d\n", tests_run);

  return result != 0;
}
