#include "optics.h"

void drawlens(unsigned int *pixels, Component c, unsigned int color);
void drawobject(unsigned int *pixels, Component c, unsigned int color);
void drawconvexlens(unsigned int *pixels, Component c, unsigned int color);
void drawconcavelens(unsigned int *pixels, Component c, unsigned int color);
void swapcomponents(Component *c1, Component *c2);
void drawfocal(unsigned int *pixels, Component c, unsigned int color);

Components newcomponents() {
    Components components = (Components) {
        .data = malloc(sizeof(Component) * MAX_COMPONENTS),
        .n = 0,
        .closest = -1,
        .selected = -1,
    };
    return components;
}

void addcomponent(Components *components, Component c) {
    components->data[components->n++] = c;
}

void drawcomponents(State *state) {
    int i;
    unsigned int color;
    for (i = 0; i < state->components.n; i++) {
        color = WHITE;
        if (state->components.selected == i)
            color = GREEN;
        if (state->components.closest == i && state->components.selected == -1)
            color = GREEN;
        drawcomponent(state->pixels, state->components.data[i], color);

        if (state->components.selected == i)
            drawfocal(state->pixels, state->components.data[i], color);
        else if ((state->components.closest == i) && (state->components.selected == -1))
            drawfocal(state->pixels, state->components.data[i], color);
    }
}

void drawcomponent(unsigned int *pixels, Component c, unsigned int color) {
    switch (c.type) {
        case CONVEX_LENS:
        case CONCAVE_LENS:
            drawlens(pixels, c, color);
            break;
        case OBJECT:
            drawobject(pixels, c, color);
        default:
            break;
    }
}

void selectcomponent(State *state) {
    int mini = -1;
    int mindist = SCREENWIDTH / 50;
    int i;
    for (i = 0; i < state->components.n; i++) {
        Component c = state->components.data[i];
        int xdist = state->mousepos.x - c.pos;
        int ydist;
        if (state->mousepos.y < MIDY - c.height)     // top
            ydist = (MIDY - c.height) - state->mousepos.y;
        else if (state->mousepos.y > MIDY + c.height)
            ydist = (MIDY + c.height) - state->mousepos.y;
        else
            ydist = 0;

        int dist = sqrt(pow(xdist, 2) + pow(ydist, 2));
        if (dist < mindist) {
            mindist = dist;
            mini = i;
        }
    }

    state->components.closest = mini;
    switch (state->mousebutton) {
        case SDL_BUTTON_LEFT:
        case SDL_BUTTON_RIGHT:
            if (state->components.selected == -1)
                state->components.selected = mini;
            break;
        default:
            state->components.selected = -1;
    }
}

void updatecomponent(State *state) { 
    switch (state->mousebutton) {
        case SDL_BUTTON_LEFT:
            state->components.data[state->components.selected].pos = state->mousepos.x;
            break;
        case SDL_BUTTON_RIGHT:
            int height = (MIDY) - state->mousepos.y;
            switch (state->components.data[state->components.selected].type) {
                case OBJECT:
                    break;
                default:
                    height = abs(height);
                    break;

            }
            state->components.data[state->components.selected].height = height;
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

void drawfocal(unsigned int *pixels, Component c, unsigned int color) {
    if (c.type == OBJECT)
        return;
    fillcircle(pixels, (v2i){c.pos + c.f, MIDY}, SCREENWIDTH/200, color);
    drawcircle(pixels, (v2i){c.pos - c.f, MIDY}, SCREENWIDTH/200, color);
}

void updatefocal(State *state, int y) {
    int off = state->components.selected == -1 ? state->components.closest : state->components.selected;
    int dy = (SCREENWIDTH/200) * y;
    Component *c = state->components.data + off;
    switch (c->type) {
        case OBJECT:
            break;
        case CONVEX_LENS:
        case CONVEX_MIRROR:
            c->f = MAX(c->f + dy, 0);
            break;
        case CONCAVE_LENS:
        case CONCAVE_MIRROR:
            c->f = MIN(c->f + dy, 0);
            break;
    }
}

void drawobject(unsigned int *pixels, Component c, unsigned int color) {
    v2i tip = (v2i){c.pos, MIDY - c.height};
    drawarrow(pixels, tip, color);
}

void drawconvexlens(unsigned int *pixels, Component c, unsigned int color) {
    double r = (double)c.height / degsin(c.angle);
    int c1 = c.pos - ((double)c.height / degtan(c.angle));
    int c2 = c.pos + ((double)c.height / degtan(c.angle));
    drawarc(pixels, (v2i){c1, MIDY}, r, -c.angle, c.angle, color);
    drawarc(pixels, (v2i){c2, MIDY}, r, 180 - c.angle, 180 + c.angle, color);

    drawline(pixels, (v2i){c.pos - r + r * degcos(c.angle), MIDY}, (v2i){c.pos + r - r * degcos(c.angle), MIDY}, 0);
}

void drawconcavelens(unsigned int *pixels, Component c, unsigned int color) {
    double r = (double)c.height / degsin(c.angle);
    int x = r * degcos(c.angle);
    int y = sqrt(pow(r, 2) - pow(x + 1, 2));
    int c1 = c.pos - (2 * r) + x;
    int c2 = c.pos + (2 * r) - x;
    drawarc(pixels, (v2i){c1, MIDY}, r, -c.angle, c.angle, color);
    drawarc(pixels, (v2i){c2, MIDY}, r, 180 - c.angle, 180 + c.angle, color);
    v2i p0 = (v2i){c.pos - 2 * (r - x), MIDY + y};
    v2i p1 = (v2i){c.pos + 2 * (r - x), MIDY + y};
    drawline(pixels, p0, p1, color);
    p0.y = p1.y = MIDY - y;
    drawline(pixels, p0, p1, color);

    drawline(pixels, (v2i){c.pos - (r - x), MIDY}, (v2i){c.pos + (r - x), MIDY}, 0);
}

void sortcomponents(Component *cs, int left, int right) {
	int i, last;

	if (left >= right)
		return;
	swapcomponents(cs + left, cs + ((left + right)/2));
	last = left;
	for (i = left + 1; i <= right; i++)
		if (cs[i].pos < cs[left].pos)
			swapcomponents(cs + ++last, cs + i);
	swapcomponents(cs + left, cs + last);
	sortcomponents(cs, left, last-1);
	sortcomponents(cs, last+1, right);
}

void swapcomponents(Component *c1, Component *c2) {
    Component temp = *c1;
    *c1 = *c2;
    *c2 = temp;
}

Component *activecomponent(Components *components) {
    if (components->selected >= 0)
        return components->data + components->selected;
    else if (components->closest >= 0)
        return components->data + components->closest;
    else
        return NULL;
}

void drawcomponentinfo(unsigned int *pixels, v2i pos, Component *c) {
    if (c == NULL)
        return;

    int px = pos.x;
    int py = pos.y;
    const int spacing = 20;
    char *str = malloc(sizeof(char) * 100);

    setfontsize(16);
    setfontcolor(WHITE);
    setfontalign(LEFT);

    char *type;
    switch (c->type) {
        case CONVEX_LENS:
            type = "Convex Lens";
            break;
        case CONCAVE_LENS:
            type = "Concave Lens";
            break;
        case CONVEX_MIRROR:
            type = "Convex Mirror";
            break;
        case CONCAVE_MIRROR:
            type = "Concave Mirror";
            break;
        case OBJECT:
            type = "Object";
            break;
    }
    drawtext(pixels, type, (v2i){px, py});

    px += spacing;

    sprintf(str, "pos: %d", c->pos);
    drawtext(pixels, str, (v2i){px, py += spacing});

    switch (c->type) {
        case CONVEX_LENS:
        case CONCAVE_LENS:
        case CONVEX_MIRROR:
        case CONCAVE_MIRROR:
            sprintf(str, "f: %d", c->f);
            drawtext(pixels, str, (v2i){px, py += spacing});
            break;
        case OBJECT:
            sprintf(str, "height: %d", c->height);
            drawtext(pixels, str, (v2i){px, py += spacing});
            
            drawtext(pixels, "Image", (v2i){px - spacing, py += spacing});
            break;
    }



    free(str);
}

