#ifndef __TIME_H_
#define __TIME_H_

#include <stdint.h>

typedef struct  {
    float delta;
    float now;
    float last;

    float frame_last;
    float frame_delay;
    float frame_time;

    uint32_t frame_rate;
    uint32_t frame_count;
} Time_State;

void time_init(uint32_t frame_rate);
void time_update(void);

#endif
