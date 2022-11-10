#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "linmath.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "global.h"

int main(int argc, char **argv) {

    render_init();

    bool quit = false;

    while (!quit) {
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

        render_begin();

        render_quad(
            (vec2){global.render.width*0.5, global.render.height*0.5},
            (vec2){50, 50},
            (vec4){0, 1, 0, 1});

        render_end();
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
