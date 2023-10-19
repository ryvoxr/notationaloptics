#include "optics.h"
#include <math.h>

void drawlinelow(u32 *pixels, v2i p1, v2i p2, u32 color);

void drawpixel(u32 *pixels, v2i p, u32 color) {
    pixels[(p.y * SCREENWIDTH) + p.x] = color;
}

void drawline(u32 *pixels, v2i p1, v2i p2, u32 color) {
    /* Bresenham's line algorithm */
}

void drawlinelow(u32 *pixels, v2i p1, v2i p2, u32 color) {
    if (abs(p2.y - p1.y) < abs(p2.x - p1.x)) {
    }
}

