#pragma once

#include <assert.h>
#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// Based on this: https://gist.github.com/sam159/0849461161e86249f849

#define mu_run_test(test)                    \
  do {                                       \
    if (mu_before_each) mu_before_each();    \
    char* message = test();                  \
    vsync();                                 \
    mu_tests_run++;                          \
    if (message) return message;             \
  } while (0)

#define mu_run_suite(test)       \
  do {                           \
    char* message = test();      \
    mu_before_each = NULL;       \
    vsync();                     \
    if (message) return message; \
  } while (0)

extern int mu_tests_run;
extern char mu_error_buffer[256];
extern void (*mu_before_each)(void);

void mu_init(void);

#define mu_run_bench(label, test)                         \
  do {                                                    \
    uint8_t _start, _end;                                 \
    uint8_t _ie;                                          \
    char* message;                                        \
    if (mu_before_each) mu_before_each();                 \
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
    mu_tests_run++;                                       \
    if (message) return message;                          \
    printf("%s: %hu\n", label, (uint8_t)(_end - _start)); \
  } while (0)

#define mu_error(format, ...)                                        \
  (sprintf(mu_error_buffer, "%s:%d" format, __FILE_NAME__, __LINE__, \
           ##__VA_ARGS__),                                           \
   mu_error_buffer)

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
