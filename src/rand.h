#pragma once

#include <stdint.h>

void rand_init(void);
uint8_t rand_next_mod(uint8_t mod);
uint8_t rand_next(void);
