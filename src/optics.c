#include "optics.h"

v2i getimagetip(Components components, int object);
void drawimage(unsigned int *pixels, Components components, int object);

void drawimages(unsigned int *pixels, Components components) {
    int i;

    int distances[components.n];
    for (i = 0; i < components.n; i++)
        distances[i] = components.data[i].pos;

    for (i = 0; i < components.n; i++) {
        if (components.data[i].type == OBJECT)
            drawimage(pixels, components, i);
    }
}

void drawimage(unsigned int *pixels, Components components, int object) {
    v2i tip = getimagetip(components, object);
}

v2i getimagetip(Components components, int object) {
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

    for (i = 0; i < n; i++)
        printf("%d ", comps[i].pos);
    putchar('\n');

    free(comps);
}

