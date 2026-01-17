#pragma once

#include <assert.h>
#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>

// Based on this: https://gist.github.com/sam159/0849461161e86249f849

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
extern char _ferror_buffer[256];

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

#define mu_error(format, ...)                                       \
  (sprintf(_ferror_buffer, "%s:%d" format, __FILE_NAME__, __LINE__, \
           ##__VA_ARGS__),                                          \
   _ferror_buffer)

#define mu_assert(expr)                 \
  do {                                  \
    if (!(expr)) {                      \
      return mu_error(" FAIL\n" #expr); \
    }                                   \
  } while (0)

#define mu_assert_eq(actual, expected, format)                 \
  do {                                                         \
    if ((actual) != (expected)) {                              \
      return mu_error(" ERR:\nACTUAL: " format " (" #actual    \
                      ")\nEXPECT: " format " (" #expected ")", \
                      actual, expected);                       \
    }                                                          \
  } while (0)
