#include "minunit.h"

int mu_tests_run;
char mu_error_buffer[256];
void (*mu_before_each)(void);

static volatile uint8_t bench_overflows;
static uint8_t bench_saved_ie;

static void bench_timer_isr(void) {
  bench_overflows++;
}

void mu_init(void) {
  mu_tests_run = 0;
  memset(mu_error_buffer, 0, sizeof(mu_error_buffer));
  mu_before_each = NULL;
}

void mu_test_setup(void) {
  if (mu_before_each) mu_before_each();
}

void mu_test_teardown(void) {
  mu_tests_run++;
  vsync();
}

void mu_bench_start(void) {
  bench_overflows = 0;
  TAC_REG = 0;
  TIMA_REG = 0;
  TMA_REG = 0;
  IF_REG &= ~TIM_IFLAG;
  add_TIM(bench_timer_isr);
  bench_saved_ie = IE_REG;
  IE_REG |= TIM_IFLAG;
  enable_interrupts();
  TAC_REG = TACF_START | TACF_4KHZ;
}

uint16_t mu_bench_end(void) {
  TAC_REG = 0;
  disable_interrupts();
  remove_TIM(bench_timer_isr);
  IE_REG = bench_saved_ie;
  enable_interrupts();
  return ((uint16_t)bench_overflows << 8) | TIMA_REG;
}
