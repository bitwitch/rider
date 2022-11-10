/*#include "app.h"*/
/*#include "render.h"*/

/*#define FENCE_POSTS_PER_WINDOW_WIDTH 2*/

/*typedef struct {*/
    /*SDL_Texture *texture;*/
    /*int w, h;*/
    /*float x, y, vx, vy;*/
/*} Background;*/

/*typedef struct {*/
    /*SDL_Texture *texture;*/
    /*int w, h;*/
    /*float speed;*/
    /*float posts[FENCE_POSTS_PER_WINDOW_WIDTH];*/
    /*float y;*/
/*} Fence;*/


/*typedef struct {*/
    /*SDL_Texture *texture;*/
    /*int w, h;*/
    /*float speed;*/
    /*float x[2];*/
    /*float y;*/
/*} Background_Loop;*/

/*static Background bg;*/
/*static Fence fence;*/
/*static Background_Loop road;*/
/*static Background_Loop ground_close;*/
/*static Background_Loop ground_far;*/

/*void background_init(void) {*/
    /*if (bg.texture == NULL) {*/
        /*bg.texture = load_texture("assets/kansas_field_bg_01.jpg");*/
        /*SDL_QueryTexture(bg.texture, NULL, NULL, &bg.w, &bg.h);*/
    /*}*/
    /*bg.x = 0;*/
    /*bg.y = 0;*/
    /*bg.vx = -0.5;*/
    /*bg.vy = 0;*/

    /*if (fence.texture == NULL) {*/
        /*fence.texture = load_texture("assets/fence_post.png");*/
        /*SDL_QueryTexture(fence.texture, NULL, NULL, &fence.w, &fence.h);*/
    /*}*/
    /*fence.y = SCREEN_HEIGHT - fence.h - 70;*/
    /*fence.speed = 22;*/
    /*float spacing = (SCREEN_WIDTH - (FENCE_POSTS_PER_WINDOW_WIDTH*fence.w)) / FENCE_POSTS_PER_WINDOW_WIDTH;*/
    /*for (int i=0; i<FENCE_POSTS_PER_WINDOW_WIDTH; ++i) {*/
        /*fence.posts[i] = i*spacing;*/
    /*}*/

    /*if (road.texture == NULL) {*/
        /*road.texture = load_texture("assets/road.jpg");*/
        /*SDL_QueryTexture(road.texture, NULL, NULL, &road.w, &road.h);*/
    /*}*/
    /*road.speed = 25;*/
    /*road.y = SCREEN_HEIGHT - road.h;*/
    /*road.x[0] = 0;*/
    /*road.x[1] = road.w;*/

    /*if (ground_close.texture == NULL) {*/
        /*ground_close.texture = load_texture("assets/grass_close.png");*/
        /*SDL_QueryTexture(ground_close.texture, NULL, NULL, &ground_close.w, &ground_close.h);*/
    /*}*/
    /*ground_close.speed = 12;*/
    /*ground_close.y = SCREEN_HEIGHT - ground_close.h - road.h;*/
    /*ground_close.x[0] = 0;*/
    /*ground_close.x[1] = ground_close.w;*/

    /*if (ground_far.texture == NULL) {*/
        /*ground_far.texture = load_texture("assets/grass_far.png");*/
        /*SDL_QueryTexture(ground_far.texture, NULL, NULL, &ground_far.w, &ground_far.h);*/
    /*}*/
    /*ground_far.speed = 3;*/
    /*ground_far.y = SCREEN_HEIGHT - ground_far.h - ground_close.h - road.h + 15;*/
    /*ground_far.x[0] = 0;*/
    /*ground_far.x[1] = ground_far.w;*/
/*}*/

/*void background_update(void) {*/
    /*bg.x += bg.vx;*/
    /*bg.y += bg.vy;*/

    /*if (bg.x + bg.w < SCREEN_WIDTH)*/
        /*bg.x = SCREEN_WIDTH - bg.w;*/

    /*for (int i=0; i<FENCE_POSTS_PER_WINDOW_WIDTH; ++i) {*/
        /*fence.posts[i] -= fence.speed;*/
        /*if (fence.posts[i] < -fence.w)*/
            /*fence.posts[i] += SCREEN_WIDTH;*/
    /*}*/

    /*for (int i=0; i<2; ++i) {*/
        /*road.x[i] -= road.speed;*/
        /*if (road.x[i] <= -road.w) */
            /*road.x[i] += 2*SCREEN_WIDTH;*/

        /*ground_close.x[i] -= ground_close.speed;*/
        /*if (ground_close.x[i] <= -ground_close.w) */
            /*ground_close.x[i] += 2*SCREEN_WIDTH;*/

        /*ground_far.x[i] -= ground_far.speed;*/
        /*if (ground_far.x[i] <= -ground_far.w) */
            /*ground_far.x[i] += 2*SCREEN_WIDTH;*/
    /*}*/

/*}*/

/*void background_render(void) {*/
    /*[>blit(bg.texture, bg.x, bg.y);<]*/
    /*for (int i=0; i<2; ++i) {*/
        /*blit(road.texture, road.x[i], road.y);*/
        /*blit(ground_close.texture, ground_close.x[i], ground_close.y);*/
        /*blit(ground_far.texture, ground_far.x[i], ground_far.y);*/
    /*}*/
    /*for (int i=0; i<FENCE_POSTS_PER_WINDOW_WIDTH; ++i)*/
        /*blit(fence.texture, fence.posts[i], fence.y);*/
/*}*/

