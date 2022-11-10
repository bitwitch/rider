#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include "linmath.h"

typedef struct {
    SDL_Window *window;
    float width;
    float height;
} Render_State;

void render_init(void);
void render_begin(void);
void render_end(void);
void render_quad(vec2 pos, vec2 size, vec4 color);


void renderer_prepare(void);
void renderer_present(void);
SDL_Texture *load_texture(char *filename);
void blit(SDL_Texture *texture, int x, int y);
void blit_scaled(SDL_Texture *texture, int x, int y, int w, int h);
void blit_rect(SDL_Texture *texture, SDL_Rect *src, int x, int y);
void fill_rect(int x, int y, int w, int h, uint32_t color);

#endif
