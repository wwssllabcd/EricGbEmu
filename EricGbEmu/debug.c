

#include "debug.h"
#include "cpu.h"
#include "mmu.h"

#define PRINTF_DEBUG(FMT,...)                         \
    if(g_is_debug){                                   \
        PRINTF_ALWAYS(FMT, ##__VA_ARGS__);            \
    }                                                 \

#define PRINTF_DEBUG_NOCRLF(FMT,...)                  \
    if(g_is_debug){                                   \
        PRINTF_ALWAYS_NOCRLF(FMT, ##__VA_ARGS__);     \
    }                                                 \

#define START_CNT (0x258900)
#define END_CNT   (0x259000)

bool g_is_debug = false;
eu32 g_cmd_cnt = 0;

bool is_debug_enable() {
    return (START_CNT <= g_cmd_cnt) && (g_cmd_cnt < END_CNT);
}

void print_ram(RamAddr ptr, eu32 len) {
   print_ram_base(ptr, len, get_ram);
}

void set_debug_flag() {
    if (is_debug_enable()) {
        if (!g_is_debug) {
            PRINTF_DEBUG(" ---- start g_cmd_cnt=%X ----", g_cmd_cnt);
            g_is_debug = true;
        }
    } else {
        if (g_is_debug) {
            PRINTF_DEBUG(" ---- end g_cmd_cnt=%X ----", g_cmd_cnt);
            g_is_debug = false;
        }
    }
}

void debug_show_reg_ram(bool is_cb_cmd, eu8 opcode, eu8 clock) {
    set_debug_flag();
    if (g_is_debug) {
        if (is_cb_cmd) {
            PRINTF_DEBUG("cbcode = %02X", opcode);
        } else {
            PRINTF_DEBUG("opcode = %02X", opcode);
        }
        PRINTF_DEBUG("cmdcnt=%X, pc=%X, af=%X, bc=%X, de=%X, hl=%X, flags=%X, sp=%X, clock=%X", g_cmd_cnt, pc->all, af->all, bc->all, de->all, hl->all, flags->all, sp->all, clock);

        print_ram(0x0, 0x10);
        print_ram(0x100, 0x10);
        print_ram(0x2320, 0x10);
        print_ram(0x8000, 0x20);
        print_ram(0x9900, 0x30);
        print_ram(0xFE00, 0x20);
        print_ram(0xFF00, 0x10);
        print_ram(0xFF40, 0x11);
        print_ram(0xFFA0, 0x20);


    }
}

void debug_show_pixels_table(eu8 frame_buffer[SCREEN_HEIGHT][SCREEN_WIDTH]) {
    PRINTF_DEBUG("-----------");
    PRINTF_DEBUG("set_pixels=%X", g_cmd_cnt);
    for (eu8 y = 0; y < SCREEN_HEIGHT; y++) {
        PRINTF_DEBUG_NOCRLF("\n");
        for (eu8 x = 0; x < SCREEN_WIDTH; x++) {
            PRINTF_DEBUG_NOCRLF("%01X ", frame_buffer[y][x]);
        }
    }
    PRINTF_DEBUG("--------");
}