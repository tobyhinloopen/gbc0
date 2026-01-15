#pragma once

#include <stdint.h>

#define buffer_height 32
#define buffer_width 8
#define buffer_size (buffer_height * buffer_width)
#define buffer_screen_height 18

extern uint8_t buffer_tiles[buffer_size];
extern uint8_t *buffer_tiles_end;

void buffer_clear(void);
