#include <SDL2/SDL.h>
#include "graphics.h"

#define MAX_COMPONENTS 5

typedef enum ComponentType {
    CONVEX_LENS,
    CONCAVE_LENS,
    CONVEX_MIRROR,
    CONCAVE_MIRROR,
    OBJECT,
} ComponentType;

typedef struct Component {
    ComponentType type;
    int pos;
    int height;
    double angle;
    int id;
    int f;
} Component;

typedef struct Components {
    Component *data;
    int n;
    int closest;
    int selected;
} Components;

typedef struct State {
    unsigned int *pixels;
    Components components;
    char mousebutton;
    v2i mousepos;
} State;

typedef struct Context {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
} Context;

void quit(State *state, Context *ctx);
void handleevents(State *state, Context *ctx);

void drawcomponents(State *state);
Components newcomponents();
void addcomponent(Components *components, Component c);
void drawcomponent(unsigned int *pixels, Component c, unsigned int color);
void selectcomponent(State *state);
void updatecomponent(State *state);
void sortcomponents(Component *cs, int left, int right);
void updatefocal(State *state, int y);
void drawarrow(unsigned int *pixels, v2i tip, unsigned int color);

void drawimages(unsigned int *pixels, Components components);

void initfreetype();
void drawtext(unsigned int *pixels, char *text, v2i pos, unsigned int color, int fontsize);
