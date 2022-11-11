#include "physics.h"
#include "global.h"

typedef struct {
    Array_List *body_list;
} Physics_State_Internal;

static Physics_State_Internal state = {0};


void physics_init(void) {
    state.body_list = array_list_create(sizeof(Body), 0);
}

void physics_update(void) {
    Body *body;

    for (size_t i = 0; i < state.body_list->length; ++i) {
        body = array_list_get(state.body_list, i);
        body->velocity[0] += body->acceleration[0] * global.time.delta;
        body->velocity[1] += body->acceleration[1] * global.time.delta;
        body->aabb.position[0] += body->velocity[0] * global.time.delta;
        body->aabb.position[1] += body->velocity[1] * global.time.delta;
    }
}

size_t physics_body_create(vec2 position, vec2 size) {
    Body body = {
        .aabb = {
            .position = { position[0], position[1] },
            .half_size = { size[0] * 0.5, size[1] * 0.5 },
        },
        .velocity = { 0, 0 },
    };

    return array_list_append(state.body_list, &body);
}

Body *physics_body_get(size_t index) {
    return array_list_get(state.body_list, index);
}

