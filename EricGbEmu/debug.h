#pragma once

#include "header.h"

#define PRINTF_DEBUG(FMT,...)                         \
    if(g_debug){                                   \
        PRINTF_ALWAYS(FMT, ##__VA_ARGS__);            \
    }                                                 \

#define PRINTF_DEBUG_NOCRLF(FMT,...)                  \
    if(g_debug){                                   \
        PRINTF_ALWAYS_NOCRLF(FMT, ##__VA_ARGS__);     \
    }         

extern bool g_debug;
extern eu32 g_cmdCnt;

void debug_show_reg_ram(bool is_cb_cmd, eu8 opcode, eu8 clock);
void debug_show_pixels_table(eu8 frame_buffer[SCREEN_HEIGHT][SCREEN_WIDTH]);
void stop_cmd_cnt(eu32 cmdCnt);