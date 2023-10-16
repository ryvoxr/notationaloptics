#include "optics.h"

void drawpixel(u32 *pixels, v2i p, u32 color) {
    pixels[(p.y * SCREENWIDTH) + p.x] = color;
}

void drawline(u32 *pixels, v2i p0, v2i p1, u32 color) {
    /* Bresenham's line algorithm */
}

