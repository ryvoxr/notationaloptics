#include <stdio.h>
#include "optics.h"
#include "utils.h"

#define ASSERT(_e, ...) if (!(_e)) { fprintf(stderr, __VA_ARGS__); exit(1); }

struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    unsigned int pixels[SCREENWIDTH * SCREENHEIGHT];
} state;

int main() {
    ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0,
            "Could not initialize SDL: %s\n", SDL_GetError());

    state.window = 
        SDL_CreateWindow(
                "Notational Optics",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                SCREENWIDTH,
                SCREENHEIGHT,
                SDL_WINDOW_SHOWN);
    ASSERT(state.window, 
            "Could not create window: %s\n", SDL_GetError());


    state.renderer = SDL_CreateRenderer(state.window, -1, 0);
    ASSERT(state.renderer,
            "Could not create renderer: %s\n", SDL_GetError());

    state.texture =
        SDL_CreateTexture(
                state.renderer,
                SDL_PIXELFORMAT_ARGB8888,
                SDL_TEXTUREACCESS_STREAMING,
                SCREENWIDTH,
                SCREENHEIGHT);
    ASSERT(state.texture,
            "Could not create texture: %s\n", SDL_GetError());

    Component convexlens = {
        .type = CONVEX_LENS,
        .pos = SCREENWIDTH/2,
        .size = 100,
        .angle = 20,
    };

    Component concavelens = {
        .type = CONCAVE_LENS,
        .pos = SCREENWIDTH/2 + 200,
        .size = 100,
        .angle = 10,
    };

    int i = 0;
    while (1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) return 0;
        }
        clearscreen(state.pixels, BLACK);
        drawline(state.pixels, (v2i){0, SCREENHEIGHT/2}, (v2i){SCREENWIDTH, SCREENHEIGHT/2}, GRAY);
        drawcomponent(state.pixels, convexlens, WHITE);
        drawcomponent(state.pixels, concavelens, WHITE);
        SDL_UpdateTexture(state.texture, NULL, state.pixels, SCREENWIDTH * sizeof(unsigned int));

        SDL_RenderClear(state.renderer);
        SDL_RenderCopy(state.renderer, state.texture, NULL, NULL);
        SDL_RenderPresent(state.renderer);
        i++;
        SDL_Delay(4);
    }
}

