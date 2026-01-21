#include "test.h"

#include <stdio.h>

#include "font_test.h"
#include "grid_test.h"
#include "minunit.h"
#include "rand_test.h"

char *all_tests(void) {
  mu_run_suite(font_test);
  // mu_run_suite(grid_test);
  // mu_run_suite(rand_test);

  return 0;
}

int test_main(void) {
  mu_init();
  char *result = all_tests();
  if (result != 0) {
    printf("%s\n", result);
  } else {
    printf("ALL TESTS PASSED\n");
  }
  printf("Tests run: %d\n", mu_tests_run);

  return result != 0;
}
