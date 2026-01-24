#pragma once

#include <assert.h>
#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "font_stdio.h"

// Based on this: https://gist.github.com/sam159/0849461161e86249f849

#define mu_run_test(test)        \
  do {                           \
    mu_test_setup();             \
    char* message = test();      \
    mu_test_teardown();          \
    if (message) return message; \
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
void mu_test_setup(void);
void mu_test_teardown(void);
void mu_bench_start(void);
uint16_t mu_bench_end(void);

#define mu_run_bench(label, test)       \
  do {                                  \
    mu_test_setup();                    \
    mu_bench_start();                   \
    char* message = test();             \
    uint16_t _cycles = mu_bench_end();  \
    mu_test_teardown();                 \
    if (message) return message;        \
    font_printf("%s: %u\n", label, _cycles); \
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
