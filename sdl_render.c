#include "sdl_render.h"

void init_renderer() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        debug_print("%s", "Could not initalize SDL renderer!");
        exit(-1);
    }
    int width = SCREEN_W;
    int height = SCREEN_H;
    int bpp = SCREEN_C;
    int flags = SDL_HWSURFACE;
}
