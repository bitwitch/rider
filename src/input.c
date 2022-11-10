#include "input.h"
#include "global.h"

static void update_key_state(uint8_t current_state, Key_State *key_state) {
    if (current_state)
        *key_state = *key_state > 0 ? KS_HELD : KS_PRESSED;
    else
        *key_state = KS_UNPRESSED;
}

void input_update() {
    const uint8_t *keyboard_state = SDL_GetKeyboardState(NULL);

    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_LEFT]], &global.input.left);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_RIGHT]], &global.input.right);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_UP]], &global.input.up);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_DOWN]], &global.input.down);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_ESCAPE]], &global.input.escape);
}
