#include "optics.h"
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

FT_Library library;   /* handle to library */
FT_Face face;         /* handle to face object */

int fontsize;
unsigned int fontcolor;
Align fontalign;

void initfreetype() {
    ASSERT(FT_Init_FreeType(&library) == 0,
            "Could not initialize FreeType\n");

    char fontpath[] = "/usr/share/fonts/liberation/LiberationMono-Regular.ttf";
    ASSERT(FT_New_Face(library, fontpath, 0, &face) == 0,
            "Could not load font: %s\n", fontpath);

    float ddpi, hdpi, vdpi;
    ASSERT(SDL_GetDisplayDPI(0, &ddpi, &hdpi, &vdpi) == 0,
            "Could not get display DPI: %s\n", SDL_GetError());

    ASSERT(FT_Set_Char_Size(face, 0, 64 * 64, hdpi, vdpi) == 0,
            "Could not set font size\n");
}

void drawtext(unsigned int *pixels, char *text, v2i pos) {
    FT_GlyphSlot slot = face->glyph;
    int pen_x = pos.x;
    int pen_y = pos.y + fontsize;

    ASSERT(FT_Set_Pixel_Sizes(face, 0, fontsize) == 0,
            "Could not set font size\n");

    switch (fontalign) {
        case LEFT:
            break;
        case CENTER:
            pen_x -= ((slot->advance.x >> 6) * strlen(text)) / 2;
            break;
        case RIGHT:
            pen_x -= (slot->advance.x >> 6) * strlen(text);
            break;
    }

    int i;
    for (i = 0; text[i]; i++) {
        ASSERT(FT_Load_Char(face, text[i], FT_LOAD_RENDER) == 0,
                "Could not load character\n");

        unsigned int x, y;
        for (y = 0; (unsigned int)y < slot->bitmap.rows; y++) {
            for (x = 0; (unsigned int)x < slot->bitmap.width; x++) {
                int px = pen_x + x + slot->bitmap_left;
                int py = pen_y + y - slot->bitmap_top;
                if (px < 0 || px >= SCREENWIDTH || py < 0 || py >= SCREENHEIGHT)
                    continue;
                unsigned int alpha = slot->bitmap.buffer[y * slot->bitmap.width + x];
                unsigned int color2 = alpha << 24 | fontcolor;
                if (alpha > 90) {
                    pixels[py * SCREENWIDTH + px] = color2;
                }
            }
        }

        pen_x += slot->advance.x >> 6;
        pen_y += slot->advance.y >> 6;
    }
}

void drawtitle(unsigned int *pixels) {
    setfontsize(16);
    setfontcolor(WHITE);
    setfontalign(RIGHT);
    drawtext(pixels, "Notational Optics", (v2i){SCREENWIDTH - 5, 0});
}

void setfontsize(int size) {
    fontsize = size;
}

void setfontcolor(unsigned int color) {
    fontcolor = color;
}

void setfontalign(Align align) {
    fontalign = align;
}

