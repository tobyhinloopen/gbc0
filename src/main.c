#include <gb/gb.h>
#include <gb/cgb.h>
#include "font_stdio.h"
#include "game.h"
#include "rand.h"
#include "test.h"

// Palettes for room tiles
static const uint16_t bg_palettes[5][4] = {
  { 0x7FFF, 0x5294, 0x294A, 0x0000 },  // 0: default (floor)
  { 0x7FFF, 0x3186, 0x18C3, 0x0000 },  // 1: wall (dark gray)
  { 0x001F, 0x7FFF, 0x001F, 0x7FFF },  // 2: target (red blink)
  { 0x7FFF, 0x02B5, 0x014A, 0x0000 },  // 3: table (brown)
  { 0x7FFF, 0x5294, 0x294A, 0x0000 },  // 4: screw
};

static const uint16_t sprite_palette[4] = {
  0x7FFF, 0x03E0, 0x0140, 0x0000,  // green robot
};

void main(void) {
  DISPLAY_ON;
  SHOW_BKG;
  if (_cpu == CGB_TYPE) {
    for (uint8_t i = 0; i < 5; i++)
      set_bkg_palette(i, 1, bg_palettes[i]);
    set_sprite_palette(0, 1, sprite_palette);
  } else {
    BGP_REG = 0xE4;
    OBP0_REG = 0xE4;
  }

  rand_init();

  if (test_main()) {
    vsync();
    return;
  }
  vsync();

  font_printf("Press A to start.\n");
  while (!(joypad() & J_A)) vsync();
  while (joypad() & J_A) vsync();

  font_clear();
  SCY_REG = 0;

  game_init();

  while(1) {
    vsync();
    game_update();
  }
}
