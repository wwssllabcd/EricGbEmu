

#include "input.h"


typedef union {
    eu8 all;
    struct {
        bool up;
        bool down;
        bool left;
        bool right;
        bool a;
        bool b;
        bool select;
        bool start;
        bool button_switch;
        bool direction_switch;
    };
}GbKey;

GbKey g_key = {
    .up = false,
    .down = false,
    .left = false,
    .right = false,
    .a = false,
    .b = false,
    .select = false,
    .start = false,
    .button_switch = false,
    .direction_switch = false,
};

// todo: 應該可設計一個 type(like flags), 對應到 0xFF00
void input_write(eu8 value) {
    // maybe reset joypad
    g_key.direction_switch = !CHECK_BIT(value, 4);
    g_key.button_switch = !CHECK_BIT(value, 5);
}

//代表 0xFF40
eu8 input_read() {
    eu8 buttons = 0b1111;
    if (g_key.direction_switch) {
        SET_BIT_TO(buttons, 0, !g_key.right);
        SET_BIT_TO(buttons, 1, !g_key.left);
        SET_BIT_TO(buttons, 2, !g_key.up);
        SET_BIT_TO(buttons, 3, !g_key.down);
    }

    if (g_key.button_switch) {
        SET_BIT_TO(buttons, 0, !g_key.a);
        SET_BIT_TO(buttons, 1, !g_key.b);
        SET_BIT_TO(buttons, 2, !g_key.select);
        SET_BIT_TO(buttons, 3, !g_key.start);
    }

    SET_BIT_TO(buttons, 4, !g_key.direction_switch);
    SET_BIT_TO(buttons, 5, !g_key.button_switch);

    return buttons;
}

void set_button(eu8 code, bool is_key_down) {
    if (code == GB_KEY_NULL) {return; }

    if (code == GB_KEY_UP) { g_key.up = is_key_down; }
    if (code == GB_KEY_DOWN) { g_key.down = is_key_down; }
    if (code == GB_KEY_LEFT) { g_key.left = is_key_down; }
    if (code == GB_KEY_RIGHT) { g_key.right = is_key_down; }
    if (code == GB_KEY_A) { g_key.a = is_key_down; }
    if (code == GB_KEY_B) { g_key.b = is_key_down; }
    if (code == GB_KEY_SELECT) { g_key.select = is_key_down; }
    if (code == GB_KEY_START) { g_key.start = is_key_down; }
}

void key_down_event(eu8 code) {
    set_button(code, true);
}

void key_up_event(eu8 code) {
    set_button(code, false);
}
