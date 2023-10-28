#include "optics.h"

void handleevent(State *state, Context *ctx, SDL_Event event);

void handleevents(State *state, Context *ctx) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        handleevent(state, ctx, event);
    }
}

void handleevent(State *state, Context *ctx, SDL_Event event) {
    switch (event.type) {
        case SDL_QUIT:
            quit(state, ctx);
            break;
        case SDL_MOUSEMOTION:
            state->mousepos = (v2i){event.motion.x, event.motion.y};
            selectcomponent(state);
            updatecomponent(state);
            break;
        case SDL_MOUSEBUTTONDOWN:
            state->mousebutton = event.button.button;
            break;
        case SDL_MOUSEBUTTONUP:
            state->mousebutton = -1;
            break;
        case SDL_MOUSEWHEEL:
            updatefocal(state, event.wheel.y);
    }
};

