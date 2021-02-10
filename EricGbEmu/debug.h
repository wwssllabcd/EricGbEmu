#pragma once

#include "header.h"

extern bool g_is_debug;
extern eu32 g_cmd_cnt;

void debug_show_reg_ram(bool is_cb_cmd, eu8 opcode, eu8 clock);
void debug_show_pixels_table(eu8 frame_buffer[SCREEN_HEIGHT][SCREEN_WIDTH]);