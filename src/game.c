/*#include <stdlib.h> // for rand*/
/*#include "render.h"*/
/*#include "game.h"*/
/*#include "background.h"*/
/*#include "player.h"*/

/*[>static int reset_timer;<]*/

/*[>static void game_reset(void);<]*/

/*[>static bool bullet_hit_ship(Entity *b);<]*/
/*[>static bool bullet_hit_player(Entity *b);<]*/
/*[>static bool collide(Entity *a, Entity *b);<]*/
/*[>static bool player_hit_ship();<]*/

/*[>static void background_init(void);<]*/
/*[>static void background_update(void);<]*/
/*[>static void background_render(void);<]*/


/*[> time variables <]*/
/*static uint64_t prev_counter;*/
/*static uint64_t performance_freq;*/

/*void game_init(void) {*/
    /*performance_freq = SDL_GetPerformanceFrequency();*/
    /*prev_counter     = SDL_GetPerformanceCounter();*/

    /*background_init();*/
    /*player_init();*/
/*}*/

/*void game_update(void) {*/
    /*static double accumulator = 0;*/
    /*static double delta_ms = 0;*/
    /*static uint64_t cur_counter = 0;*/
    /*static uint64_t counter_elapsed = 0;*/

    /*cur_counter = SDL_GetPerformanceCounter();*/
    /*counter_elapsed = cur_counter - prev_counter;*/
    /*delta_ms = (1000.0f * (double)counter_elapsed) / (double)performance_freq;*/
    /*prev_counter = cur_counter;*/

    /*accumulator += delta_ms;*/
    /*while (accumulator > TIME_STEP) {*/
        /*background_update();*/
        /*tornado_update(TIME_STEP);*/
        /*player_update(TIME_STEP);*/
        /*debris_update(TIME_STEP);*/
        /*accumulator -= TIME_STEP;*/
    /*}*/
/*}*/

/*void game_render(void) {*/
    /*background_render();*/
    /*player_render();*/
/*}*/

