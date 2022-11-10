#ifndef __INPUT_H_
#define __INPUT_H_

typedef enum {
    INPUT_KEY_LEFT,
    INPUT_KEY_RIGHT,
    INPUT_KEY_UP,
    INPUT_KEY_DOWN,
    INPUT_KEY_ESCAPE,
    INPUT_KEY_COUNT
} Input_Key;

typedef enum {
    KS_UNPRESSED,
    KS_PRESSED,
    KS_HELD
} Key_State;

typedef struct {
    Key_State left;
    Key_State right;
    Key_State up;
    Key_State down;
    Key_State escape;
} Input_State;

void input_update(void);

#endif 
