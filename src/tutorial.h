#pragma once

#include <stdint.h>
#include <stdbool.h>

#define TUTORIAL_TIMER_SECONDS 10
#define TUTORIAL_TIMER_FRAMES (TUTORIAL_TIMER_SECONDS * 60)

#define TEST_001 0
#define TEST_002 1
#define TEST_030 2
#define TEST_COUNT 3

#define TUTORIAL_RUNNING 0
#define TUTORIAL_PASS    1
#define TUTORIAL_FAIL    2
#define TUTORIAL_DONE    3

extern uint8_t tutorial_current_test;
extern uint8_t tutorial_result;
extern uint16_t tutorial_timer;

void tutorial_init(void);
void tutorial_update(void);
void tutorial_render_hud(void);
bool tutorial_is_done(void);
