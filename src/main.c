#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "linmath.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "global.h"

static bool quit = false;
static vec2 pos;

static void input_handle(void) {
    if (global.input.left == KS_PRESSED || global.input.left == KS_HELD)
        pos[0] -= 500 * global.time.delta;
    if (global.input.right == KS_PRESSED || global.input.right == KS_HELD)
        pos[0] += 500 * global.time.delta;
    if (global.input.up == KS_PRESSED || global.input.up == KS_HELD)
        pos[1] += 500 * global.time.delta;
    if (global.input.down == KS_PRESSED || global.input.down == KS_HELD)
        pos[1] -= 500 * global.time.delta;
    if (global.input.escape == KS_PRESSED || global.input.escape == KS_HELD)
        quit = true;
}

int main(int argc, char **argv) {
    time_init(60);
    config_init();
    render_init();

    pos[0] = global.render.width * 0.5;
    pos[1] = global.render.height * 0.5;

    bool quit = false;

    while (!quit) {
        time_update();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
            case SDL_QUIT: 
                quit = true; 
                break;
            default: 
                break;
            }
        }

        input_update();
        input_handle();

        render_begin();

        render_quad(
            pos,
            (vec2){50, 50},
            (vec4){0, 1, 0, 1});

        render_end();
        time_update_late();
    }

    /*game_init();*/

    /*while (!app.quit) {*/
        /*renderer_prepare();*/
        /*do_input();*/
        /*game_update();*/
        /*game_render();*/
        /*renderer_present();*/
    /*}*/

    return 0;
}

