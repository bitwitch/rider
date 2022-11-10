#ifndef __ENTITY_H__
#define __ENTITY_H__

typedef enum {
    SIDE_PLAYER,
    SIDE_ENEMY
} Side;
 
typedef struct Entity Entity;

struct Entity {
    float x, y, vx, vy;
    int w, h;
    float speed;
    int health;
    Side side;
    SDL_Texture *texture;
};

typedef struct Explosion Explosion;

struct Explosion {
    float x, y;
    float vx, vy;
    int r,g,b,a;
    Explosion *next;
};

typedef struct Debris Debris;

struct Debris {
	float x;
	float y;
	float vx;
	float vy;
	SDL_Rect rect;
	SDL_Texture *texture;
	int life;
	Debris *next;
};

#endif
