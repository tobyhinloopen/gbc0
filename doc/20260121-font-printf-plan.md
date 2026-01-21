# Font Printf Implementation Plan

## Overview
Replace stdio.h printf with custom font_printf() using variable-width font rendering.

## Step 1: Multi-line String Rendering to Tiles

Create `font_render_text()` that renders a string to a rectangular tile buffer with:
- Word wrapping at tile boundary
- Newline support (`\n`)
- Returns render stats (lines used, characters rendered)

```c
typedef struct {
    const char *remainder;  // Unrendered text (if overflow)
    uint8_t lines_used;
} font_render_text_result_t;

font_render_text_result_t font_render_text(
    uint8_t *tiles,
    uint8_t tiles_width,   // tiles per row
    uint8_t tiles_height,  // max rows
    int8_t dx,             // starting x offset in pixels
    int8_t dy,             // starting y offset in pixels
    const char *text
);
```

Implementation:
- Loop calling `font_render_line_1bpp()` for each line
- On `\n` or word wrap: advance to next tile row (y += 8 pixels)
- Stop when tiles_height rows exhausted or text finished

---

## Step 2: Render Text Directly to Screen

Create `font_print()` that renders text to VRAM using global cursor:

```c
void font_print(const char *text);
```

Behavior:
- Renders to background starting at `font_cursor_x`, `font_cursor_y`
- Same width/height behavior as `font_printf()`
- Updates cursor position after rendering

Implementation:
- Use static tile buffer (20 tiles wide max)
- Call `font_render_text()` to render to buffer
- Copy rendered tiles to VRAM using `set_bkg_data()`
- Update tile map using `set_bkg_tiles()`
- Update `font_cursor_x`, `font_cursor_y`

---

## Step 3: Printf Variant to Tiles

Create `font_sprintf()` that formats and renders to tile buffer:

```c
font_render_text_result_t font_sprintf(
    uint8_t *tiles,
    uint8_t tiles_width,
    uint8_t tiles_height,
    const char *fmt,
    ...
);
```

Supported format specifiers (minimal set):
- `%d` / `%i` - signed decimal
- `%u` - unsigned decimal
- `%x` / `%X` - hexadecimal
- `%s` - string
- `%c` - character
- `%%` - literal %

Implementation:
- Small format buffer (32-64 bytes) or render directly
- Parse format string, expand specifiers
- Call `font_render_text()` with expanded string

---

## Step 4: Printf Directly to Screen

Create `font_printf()` as a console-style API with global cursor state:

```c
// Global cursor state
extern uint8_t font_cursor_x;  // pixel position
extern uint8_t font_cursor_y;  // pixel position

void font_printf(const char *fmt, ...);
```

Behavior:
- Renders to background starting at `font_cursor_x`, `font_cursor_y`
- Width: 20 tiles (screen width = 160 pixels)
- Height: remaining rows until bottom of background (18 tiles)
- Updates cursor position after rendering
- Newline: resets x to 0, advances y by 8
- Auto-wraps at screen edge

```c
// Usage
font_cursor_x = 0;
font_cursor_y = 0;
font_printf("Score: %d\n", score);  // renders, advances cursor
font_printf("Lives: %d", lives);    // continues from cursor
```

Implementation:
- Format string to temp buffer
- Call `font_render_text()` with screen dimensions
- Copy tiles to VRAM at cursor position
- Update `font_cursor_x`, `font_cursor_y`

---

## Remove stdio.h Dependency

After implementation:
1. Remove `#include <stdio.h>` from all files
2. Replace `printf()` calls with `font_printf()`
3. Test build without stdio linkage

---

## API Summary

```c
// Low-level (to tile buffer)
font_render_line_result_t font_render_line_1bpp(...);  // existing
font_render_text_result_t font_render_text(...);       // step 1
font_render_text_result_t font_sprintf(...);           // step 3

// High-level (to screen, with cursor)
void font_print(const char *text);                     // step 2
void font_printf(const char *fmt, ...);                // step 4

// Cursor control
extern uint8_t font_cursor_x;  // pixel x (0-159)
extern uint8_t font_cursor_y;  // pixel y (0-143)
```

---

## ROM Cost Estimate

- Integer formatting (itoa): ~100-150 bytes
- Format parsing: ~100-150 bytes
- VRAM copy helpers: ~50 bytes
- **Total: ~300-400 bytes**

vs stdio printf: typically 1-2KB

---

## Notes

- Consider: static vs dynamic tile buffer allocation
- Consider: tile index allocation strategy for VRAM
- Word wrap: break on space, or mid-word if no space fits?
