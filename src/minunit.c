#include "minunit.h"

int mu_tests_run;
char mu_error_buffer[256];
void (*mu_before_each)(void);

void mu_init(void) {
  mu_tests_run = 0;
  memset(mu_error_buffer, 0, sizeof(mu_error_buffer));
  mu_before_each = NULL;
}
