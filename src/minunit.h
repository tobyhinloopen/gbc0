#pragma once

#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>

// Based on this: https://gist.github.com/sam159/0849461161e86249f849

#define mu_assert(message, test) \
  do {                           \
    if (!(test)) return message; \
  } while (0)

#define mu_run_test(test)        \
  do {                           \
    char* message = test();      \
    vsync();                     \
    tests_run++;                 \
    if (message) return message; \
  } while (0)

#define mu_run_suite(test)       \
  do {                           \
    char* message = test();      \
    vsync();                     \
    if (message) return message; \
  } while (0)

extern int tests_run;

#define mu_run_bench(label, test)                         \
  do {                                                    \
    uint8_t _start, _end;                                 \
    uint8_t _ie;                                          \
    char* message;                                        \
    _ie = IE_REG;                                         \
    disable_interrupts();                                 \
    TAC_REG = 0x00;                                       \
    DIV_REG = 0;                                          \
    TIMA_REG = 0;                                         \
    TMA_REG = 0;                                          \
    TAC_REG = TACF_START | TACF_4KHZ;                     \
    _start = TIMA_REG;                                    \
    message = test();                                     \
    _end = TIMA_REG;                                      \
    IE_REG = _ie;                                         \
    if (_ie) enable_interrupts();                         \
    tests_run++;                                          \
    if (message) return message;                          \
    printf("%s: %hu\n", label, (uint8_t)(_end - _start)); \
  } while (0)
