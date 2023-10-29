#include "optics.h"

/* Object represents both optical objects and images */
typedef struct Object {
    int pos;
    int d;
    int h;
    int image;
} Object;

void drawimage(unsigned int *pixels, Components components, int object);
void calculateimage(Object *o, Component *c);

void drawimages(unsigned int *pixels, Components components) {
    int i;

    for (i = 0; i < components.n; i++) {
        if (components.data[i].type == OBJECT)
            drawimage(pixels, components, i);
    }
}

void drawimage(unsigned int *pixels, Components components, int objecti) {
    int n, i, j;
    n = 0;
    for (i = 0; i < components.n; i++)
        if (components.data[i].type != OBJECT)
            n++;

    Component *comps = malloc(sizeof(Component) * n);
    j = 0;
    for (i = 0; i < components.n; i++)
        if (components.data[i].type != OBJECT)
            comps[j++] = components.data[i];
    sortcomponents(comps, 0, n - 1);

    Object o = { components.data[objecti].pos, NAN, components.data[objecti].height, 0 };
    int lastpos = o.pos;
    for (i = 0; i < n; i++) {
        if (lastpos > comps[i].pos)
            continue;
        lastpos = o.pos;
        calculateimage(&o, comps + i);
    }

    if (o.image) {
        unsigned int color = o.d > 0 ? GREEN : RED;
        drawarrow(pixels, (v2i){o.pos, MIDY - o.h}, color);
    }

    free(comps);
}

/* calculateimage: calculates and fills values for o */
void calculateimage(Object *o, Component *c) {
    int d_o = c->pos - o->pos;
    int h_o = o->h;
    if (d_o - c->f == 0 || d_o == 0) {
        o->image = 0;
        return;
    }
    int d_i = (d_o * c->f) / (d_o - c->f);
    int h_i = (-d_i * h_o) / d_o;
    o->pos = c->pos + d_i;
    o->h = h_i;
    o->d = d_i;
    o->image = 1;
}

