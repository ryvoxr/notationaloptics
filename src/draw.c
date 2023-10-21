#include "optics.h"
#include "utils.h"
#include <math.h>

void drawlinelow(unsigned int *pixels, v2i p0, v2i p1, unsigned int color);
void drawlinehigh(unsigned int *pixels, v2i p0, v2i p1, unsigned int color);
void drawlinelowthick(unsigned int *pixels, v2i p0, v2i p1, unsigned int color);
void drawlinehighthick(unsigned int *pixels, v2i p0, v2i p1, unsigned int color);
v2i shifttooctant(v2i p, v2i offset, int octant);

void drawpixel(unsigned int *pixels, v2i p, unsigned int color) {
    pixels[(p.y * SCREENWIDTH) + p.x] = color;
}

void drawline(unsigned int *pixels, v2i p0, v2i p1, unsigned int color) {
    if (abs(p1.y - p0.y) < abs(p1.x - p0.x)) {
        if (p0.x > p1.x) {
            drawlinelow(pixels, p1, p0, color);
        } else {
            drawlinelow(pixels, p0, p1, color);
        }
    } else {
        if (p0.y > p1.y) {
            drawlinehigh(pixels, p1, p0, color);
        } else {
            drawlinehigh(pixels, p0, p1, color);
        }
    }
}

void drawlinelow(unsigned int *pixels, v2i p0, v2i p1, unsigned int color) {
    int dx = p1.x - p0.x;
    int dy = p1.y - p0.y;
    int yi = 1;
    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }
    int D = (2 * dy) - dx;
    int y = p0.y;

    int x;
    for (x = p0.x; x < p1.x; x++) {
        drawpixel(pixels, (v2i){x, y}, color);
        if (D > 0) {
            y = y + yi;
            D = D + (2 * (dy - dx));
        } else {
            D = D + 2 * dy;
        }
    }
}

void drawlinehigh(unsigned int *pixels, v2i p0, v2i p1, unsigned int color) {
    int dx = p1.x - p0.x;
    int dy = p1.y - p0.y;
    int xi = 1;
    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }
    int D = (2 * dx) - dy;
    int x = p0.x;

    int y;
    for (y = p0.y; y < p1.y; y++) {
        drawpixel(pixels, (v2i){x, y}, color);
        if (D > 0) {
            x = x + xi;
            D = D + (2 * (dx - dy));
        } else {
            D = D + 2 * dx;
        }
    }
}

void drawlinethick(unsigned int *pixels, v2i p0, v2i p1, unsigned int color) {
    if (abs(p1.y - p0.y) < abs(p1.x - p0.x)) {
        if (p0.x > p1.x) {
            drawlinelowthick(pixels, p1, p0, color);
        } else {
            drawlinelowthick(pixels, p0, p1, color);
        }
    } else {
        if (p0.y > p1.y) {
            drawlinehighthick(pixels, p1, p0, color);
        } else {
            drawlinehighthick(pixels, p0, p1, color);
        }
    }
}

void drawlinelowthick(unsigned int *pixels, v2i p0, v2i p1, unsigned int color) {
    int dx = p1.x - p0.x;
    int dy = p1.y - p0.y;
    int yi = 1;
    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }
    int D = (2 * dy) - dx;
    int y = p0.y;

    int x;
    for (x = p0.x; x < p1.x; x++) {
        drawpixel(pixels, (v2i){x, y}, color);
        drawpixel(pixels, (v2i){x, y - 1}, color);
        if (D > 0) {
            y = y + yi;
            D = D + (2 * (dy - dx));
        } else {
            D = D + 2 * dy;
        }
    }
}

void drawlinehighthick(unsigned int *pixels, v2i p0, v2i p1, unsigned int color) {
    int dx = p1.x - p0.x;
    int dy = p1.y - p0.y;
    int xi = 1;
    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }
    int D = (2 * dx) - dy;
    int x = p0.x;

    int y;
    for (y = p0.y; y < p1.y; y++) {
        drawpixel(pixels, (v2i){x, y}, color);
        drawpixel(pixels, (v2i){x, y - 1}, color);
        if (D > 0) {
            x = x + xi;
            D = D + (2 * (dx - dy));
        } else {
            D = D + 2 * dx;
        }
    }
}

void fillcircle(unsigned int *pixels, v2i p, int r, unsigned int color) {
    int x = r - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (r << 1);

    while (x >= y) {
        drawline(pixels, (v2i){p.x + y, p.y + x}, (v2i){p.x - y, p.y + x}, color);
        drawline(pixels, (v2i){p.x + x, p.y + y}, (v2i){p.x - x, p.y + y}, color);
        drawline(pixels, (v2i){p.x - y, p.y - x}, (v2i){p.x + y, p.y - x}, color);
        drawline(pixels, (v2i){p.x - x, p.y - y}, (v2i){p.x + x, p.y - y}, color);

        if (err <= 0) {
            y++;
            err += dy;
            dy += 2;
        }

        if (err > 0) {
            x--;
            dx += 2;
            err += dx - (r << 1);
        }
    }
}

void drawcircle(unsigned int *pixels, v2i p, int r, unsigned int color) {
    int x = r - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (r << 1);

    while (x >= y) {
        drawpixel(pixels, (v2i){p.x + y, p.y + x}, color);
        drawpixel(pixels, (v2i){p.x - y, p.y + x}, color);
        drawpixel(pixels, (v2i){p.x + x, p.y + y}, color);
        drawpixel(pixels, (v2i){p.x - x, p.y + y}, color);
        drawpixel(pixels, (v2i){p.x - y, p.y - x}, color);
        drawpixel(pixels, (v2i){p.x + y, p.y - x}, color);
        drawpixel(pixels, (v2i){p.x - x, p.y - y}, color);
        drawpixel(pixels, (v2i){p.x + x, p.y - y}, color);

        if (err <= 0) {
            y++;
            err += dy;
            dy += 2;
        }

        if (err > 0) {
            x--;
            dx += 2;
            err += dx - (r << 1);
        }
    }
}

/* shifttooctant: returns p with offset shifted to octant */
v2i shifttooctant(v2i p, v2i offest, int octant) {
    switch (octant) {
        case 0: return (v2i){p.x + offest.x, p.y + offest.y};
        case 1: return (v2i){p.x + offest.y, p.y + offest.x};
        case 2: return (v2i){p.x - offest.y, p.y + offest.x};
        case 3: return (v2i){p.x - offest.x, p.y + offest.y};
        case 4: return (v2i){p.x - offest.x, p.y - offest.y};
        case 5: return (v2i){p.x - offest.y, p.y - offest.x};
        case 6: return (v2i){p.x + offest.y, p.y - offest.x};
        case 7: return (v2i){p.x + offest.x, p.y - offest.y};
        default: return (v2i){0, 0};
    }
}

void drawarc(unsigned int *pixels, v2i p, int r, double start, double end, unsigned int color) {
    int x = r - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (r << 1);

    if (end - start >= 360) {
        fillcircle(pixels, p, r, color);
        return;
    }

    /* normalize angles: [0,360) */
    start = degnormalize(start);
    end = degnormalize(end);
    if (start > end) {
        double temp = start;
        start = end;
        end = temp;
    }

    int startoctant = (int)start / 45;
    int endoctant = (int)end / 45;

    while (x >= y) {
        /* draw full octants */
        for (int i = startoctant + 1; i < endoctant; i++)
            drawpixel(pixels, shifttooctant(p, (v2i){x, y}, i), color);

        /* draw partial octants */
        v2i sp = shifttooctant(p, (v2i){x, y}, startoctant);
        if (x < (r * degcos(fmod(start, 45))))
            drawpixel(pixels, sp, color);
        v2i ep = shifttooctant(p, (v2i){x, y}, endoctant);
        if (x > (r * degcos(fmod(end, 45))))
            drawpixel(pixels, ep, color);

        if (err <= 0) {
            y++;
            err += dy;
            dy += 2;
        }

        if (err > 0) {
            x--;
            dx += 2;
            err += dx - (r << 1);
        }
    }
}

void fillarc(unsigned int *pixels, v2i p, int r, double start, double end, unsigned int color) {
    int x = r - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (r << 1);

    if (end - start >= 360) {
        fillcircle(pixels, p, r, color);
        return;
    }

    /* normalize angles: [0,360) */
    start = degnormalize(start);
    end = degnormalize(end);
    if (start > end) {
        double temp = start;
        start = end;
        end = temp;
    }

    int startoctant = (int)start / 45;
    int endoctant = (int)end / 45;

    while (x >= y) {
        /* draw full octants */
        for (int i = startoctant + 1; i < endoctant; i++) {
            v2i p1 = shifttooctant(p, (v2i){x, y}, i);
            drawlinethick(pixels, p, p1, color);
        }

        /* draw partial octants */
        v2i sp = shifttooctant(p, (v2i){x, y}, startoctant);
        if (x < (r * degcos(fmod(start, 45))))
            drawlinethick(pixels, p, sp, color);
        v2i ep = shifttooctant(p, (v2i){x, y}, endoctant);
        if (x > (r * degcos(fmod(end, 45))))
            drawlinethick(pixels, p, ep, color);

        if (err <= 0) {
            y++;
            err += dy;
            dy += 2;
        }

        if (err > 0) {
            x--;
            dx += 2;
            err += dx - (r << 1);
        }
    }
}
