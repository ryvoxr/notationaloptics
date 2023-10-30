#include "utils.h"

#define SCREENWIDTH  1920
#define SCREENHEIGHT 1080
#define MIDX (SCREENWIDTH/2)
#define MIDY (SCREENHEIGHT/2)
#define FONTSIZE 16

typedef struct v2_s  { double x, y; } v2;
typedef struct v2i_s { int x, y; } v2i;

enum Colors {
    RED     = 0xFF0000,
    GREEN   = 0x00FF00,
    BLUE    = 0x0000FF,
    BLACK   = 0x000000,
    WHITE   = 0xFFFFFF,
    GRAY    = 0x808080,
    PINK    = 0xFFC0CB,
    MAGENTA = 0xFF00FF,
};

void drawpixelraw(unsigned int *pixels, v2i p, unsigned int color);
int drawpixel(unsigned int *pixels, v2i p, unsigned int color);
void clearscreen(unsigned int *pixels, unsigned int color);
void drawline(unsigned int *pixels, v2i p0, v2i p1, unsigned int color);
void drawlinethick(unsigned int *pixels, v2i p0, v2i p1, unsigned int color);
void fillcircle(unsigned int *pixels, v2i p, int r, unsigned int color);
void drawcircle(unsigned int *pixels, v2i p, int r, unsigned int color);
void drawarc(unsigned int *pixels, v2i p, int r, double start, double end, unsigned int color);
void fillarc(unsigned int *pixels, v2i p, int r, double start, double end, unsigned int color);
