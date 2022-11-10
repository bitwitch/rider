#ifndef __GLOBAL_H_
#define __GLOBAL_H_

#include "config.h"
#include "input.h"
#include "time.h"
#include "render.h"

typedef struct {
    Config_State config;
    Input_State input;
    Time_State time;
    Render_State render;
} Global;

extern Global global;

#endif

