#pragma once

#include "header.h"

enum {
    GB_KEY_NULL = 0,
    GB_KEY_UP,
    GB_KEY_DOWN,
    GB_KEY_LEFT,
    GB_KEY_RIGHT,
    GB_KEY_A,
    GB_KEY_B,
    GB_KEY_SELECT,
    GB_KEY_START,
};


void input_write(eu8 value);
eu8 input_read();

void key_down_event(eu8 gb_code);
void key_up_event(eu8 gb_code);

