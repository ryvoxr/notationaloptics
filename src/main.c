#include <stdio.h>
#include "optics.h"

int main() {
    ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0,
            "Could not initialize SDL: %s\n", SDL_GetError());

    Context ctx;

    ctx.window = 
        SDL_CreateWindow(
                "Notational Optics",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                SCREENWIDTH,
                SCREENHEIGHT,
                SDL_WINDOW_SHOWN);
    ASSERT(ctx.window, 
            "Could not create window: %s\n", SDL_GetError());


    ctx.renderer = SDL_CreateRenderer(ctx.window, -1, 0);
    ASSERT(ctx.renderer,
            "Could not create renderer: %s\n", SDL_GetError());

    ctx.texture =
        SDL_CreateTexture(
                ctx.renderer,
                SDL_PIXELFORMAT_ARGB8888,
                SDL_TEXTUREACCESS_STREAMING,
                SCREENWIDTH,
                SCREENHEIGHT);
    ASSERT(ctx.texture,
            "Could not create texture: %s\n", SDL_GetError());

    initfreetype();

    State state = {
        .pixels = malloc(sizeof(unsigned int) * SCREENWIDTH * SCREENHEIGHT),
        .components = newcomponents(),
        .mousebutton = -1,
        .mousepos = (v2i){0, 0},
    };

    Component convexlens = {
        .type = CONVEX_LENS,
        .pos = MIDX - 60,
        .height = 100,
        .angle = 20,
        .f = 100,
    };

    Component concavelens = {
        .type = CONCAVE_LENS,
        .pos = MIDX + 200,
        .height = 100,
        .angle = 10,
        .f = -200,
    };

    Component object = {
        .type = OBJECT,
        .pos = MIDX - 200,
        .height = 50,
        .angle = 0,
        .f = 0,
    };

    addcomponent(&state.components, convexlens);
    addcomponent(&state.components, concavelens);
    addcomponent(&state.components, object);


    while (1) {
        handleevents(&state, &ctx);

        clearscreen(state.pixels, BLACK);
        drawline(state.pixels, (v2i){0, MIDY}, (v2i){SCREENWIDTH, MIDY}, GRAY);
        drawcomponents(&state);
        drawimages(state.pixels, state.components);
        drawtitle(state.pixels);

        drawcomponentinfo(state.pixels, (v2i){5, 0}, activecomponent(&state.components));

        SDL_UpdateTexture(ctx.texture, NULL, state.pixels, SCREENWIDTH * sizeof(unsigned int));
        SDL_RenderClear(ctx.renderer);
        SDL_RenderCopy(ctx.renderer, ctx.texture, NULL, NULL);
        SDL_RenderPresent(ctx.renderer);

        SDL_Delay(4);
    }
}

void quit(State *state, Context *ctx) {
    free(state->pixels);
    free(state->components.data);
    SDL_DestroyTexture(ctx->texture);
    SDL_DestroyRenderer(ctx->renderer);
    SDL_DestroyWindow(ctx->window);
    SDL_Quit();
    exit(0);
}

