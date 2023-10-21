#include "optics.h"
#include "utils.h"

void drawlens(unsigned int *pixels, Component c, unsigned int color);
void drawconvexlens(unsigned int *pixels, Component c, unsigned int color);
void drawconcavelens(unsigned int *pixels, Component c, unsigned int color);

void drawcomponent(unsigned int *pixels, Component c, unsigned int color) {
    switch (c.type) {
        case CONVEX_LENS:
        case CONCAVE_LENS:
            drawlens(pixels, c, color);
            break;
        default:
            break;
    }
}

void drawlens(unsigned int *pixels, Component c, unsigned int color) {
    switch (c.type) {
        case CONVEX_LENS:
            drawconvexlens(pixels, c, color);
            break;
        case CONCAVE_LENS:
            drawconcavelens(pixels, c, color);
            break;
        default:
            break;
    }
}

void drawconvexlens(unsigned int *pixels, Component c, unsigned int color) {
    double r = (double)c.size / degsin(c.angle);
    int c1 = c.pos - ((double)c.size / degtan(c.angle));
    int c2 = c.pos + ((double)c.size / degtan(c.angle));
    drawarc(pixels, (v2i){c1, SCREENHEIGHT/2}, r, -c.angle, c.angle, color);
    drawarc(pixels, (v2i){c2, SCREENHEIGHT/2}, r, 180 - c.angle, 180 + c.angle, color);
}

void drawconcavelens(unsigned int *pixels, Component c, unsigned int color) {
    double r = (double)c.size / degsin(c.angle);
    int x = r * degcos(c.angle);
    int y = sqrt(pow(r, 2) - pow(x + 1, 2));
    int c1 = c.pos - (2 * r) + x;
    int c2 = c.pos + (2 * r) - x;
    drawarc(pixels, (v2i){c1, SCREENHEIGHT/2}, r, -c.angle, c.angle, color);
    drawarc(pixels, (v2i){c2, SCREENHEIGHT/2}, r, 180 - c.angle, 180 + c.angle, color);
    v2i p0 = (v2i){c.pos - 2 * (r - x), SCREENHEIGHT/2 + y};
    v2i p1 = (v2i){c.pos + 2 * (r - x), SCREENHEIGHT/2 + y};
    drawline(pixels, p0, p1, color);
    p0.y = p1.y = SCREENHEIGHT/2 - y;
    drawline(pixels, p0, p1, color);
}

