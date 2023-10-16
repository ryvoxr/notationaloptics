#include <stdio.h>
#include "optics.h"

#define ASSERT(_e, ...) if (!(_e)) { fprintf(stderr, __VA_ARGS__); exit(1); }

struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    u32 pixels[SCREENWIDTH * SCREENHEIGHT];
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

    memset(state.pixels, 0x00, SCREENWIDTH * SCREENHEIGHT * sizeof(unsigned int));
    v2i p1 = { 0, 0 };
    v2i p2 = { 50, SCREENHEIGHT };
    drawline(state.pixels, p1, p2, 0xFFFF00FF);

    SDL_UpdateTexture(state.texture, NULL, state.pixels, SCREENWIDTH * sizeof(u32));

    SDL_RenderClear(state.renderer);
    SDL_RenderCopy(state.renderer, state.texture, NULL, NULL);
    SDL_RenderPresent(state.renderer);

    while (1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) return 0;
        }
    }
}
