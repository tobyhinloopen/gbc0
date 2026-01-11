#include "rand.h"
#include <rand.h>
#include <gb/gb.h>

void rand_init(void) {
  initrand(sys_time);
}

uint8_t rand_next(void) {
  return rand();
}

uint8_t rand_next_mod(uint8_t mod) {
  return rand() % mod;
}
