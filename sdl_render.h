#ifndef SDL_RENDER_H
#define SDL_RENDER_H

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#include "main.h"
#include "ppu.h"

#define TRANSPARENT_PIXEL   0x030201

void init_renderer();
void update_renderer();
void clear_renderer(const palette_pixel_t *pixel);
void put_pixel(const enum pixel_type *type, int x, int y, const palette_pixel_t *color, uint8_t alpha);
int get_pixel(SDL_Surface *surface, int x, int y);
void setTransparentPixel(int x, int y);
_Bool isTransparentPixel(int x, int y);


#endif
