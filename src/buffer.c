#include "buffer.h"

#include <string.h>

uint8_t buffer_tiles[buffer_size];
uint8_t *buffer_tiles_end = buffer_tiles + buffer_size;

void buffer_clear(void) {
  uint16_t n = buffer_size;
  uint8_t *p = buffer_tiles;
  while (n) {
    *p++ = 0;
    --n;
  }
}
