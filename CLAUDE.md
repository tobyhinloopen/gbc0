# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Game Boy Color game/demo written in C targeting GBDK (Game Boy Developers Kit). Currently focused on variable-width font rendering.

## Build Commands

```bash
make          # Build bin/gbc0.gb ROM
make run      # Build and run in emulator (SameBoy on macOS, BGB on Linux)
make test     # Build and run test ROM, outputs bin/gbc0_test.png
make clean    # Remove obj/ and bin/ directories
```

The GBDK toolchain is expected at `gbdk/` (configurable via `GBDK_HOME` env var).

## Testing

Tests use MinUnit-style macros from `src/minunit.h`:
- `mu_run_test(test_func)` - Run a test function
- `mu_run_suite(suite_func)` - Run a test suite
- `mu_assert(expr)` - Assert expression is true
- `mu_assert_eq(actual, expected, format)` - Assert equality with printf format

Test files follow `*_test.c` / `*_test.h` naming. Test suites are registered in `src/test.c` via `mu_run_suite()`.

When compiled with `-DTEST_ONLY`, `main.c` calls `test_main()` which runs all tests and prints results to the Game Boy screen. The test ROM runs in an emulator for 5 seconds and captures a screenshot to `bin/gbc0_test.png` - read this file to see test output.

## Architecture

**Modules:**
- `font.*` + `font_data.*` - Variable-width font rendering to 1bpp tile data
- `grid.*` - 6×32 game grid with block placement logic
- `rand.*` - Random number generation wrapper
- `renderer.*` - Display rendering (stub)

**Key constraints:**
- All code runs on Game Boy Color hardware (8-bit CPU, limited RAM)
- Display uses 8×8 pixel tiles; variable-width text renders across multiple tiles
- Uses GBDK headers: `<gb/gb.h>` for core API, `<gb/cgb.h>` for color features

## Code Style

- Compact, self-documenting code following Clean Code principles (Robert C. Martin)
- Prefer TDD - write tests first
- Assembly output is written to `obj/*.asm` for inspection

## External Tools

- Tilemap editing: gbmb18 & gbtd22
- Assembly optimization reference: https://github.com/pret/pokecrystal/wiki/Optimizing-assembly-code
