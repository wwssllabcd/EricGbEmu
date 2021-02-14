

#include "debug.h"
#include "cpu.h"
#include "mmu.h"
#include <stdio.h>

#define START_CNT (0)
#define END_CNT   (0)

//#define START_CNT (0xFFFFFFF)
//#define END_CNT   (0xFFFFFFF)

//#define START_CNT (0x4BD000)
//#define END_CNT   (0x4BE000)

bool g_debug = false;
eu32 g_cmdCnt = 0;

void print_ram(RamAddr ptr, eu32 len) {
   print_ram_base(ptr, len, get_ram);
}

void set_debug_flag() {
    if ((START_CNT <= g_cmdCnt) && (g_cmdCnt < END_CNT)) {
        g_debug = true;
    } else {
        g_debug = false;
        }

    if (g_cmdCnt < START_CNT) {
        if ((g_cmdCnt % 0x1000) == 0) {
            g_debug = true;
    } else {
            g_debug = false;
        }
    }
}

void show_reg_ram(bool is_cb_cmd, eu8 opcode, eu8 clock) {
        if (is_cb_cmd) {
        printf("\n\nccnt=%X, cbc=%02X, ", g_cmdCnt, opcode);
        } else {
        printf("\n\nccnt=%X, opc=%02X, ", g_cmdCnt, opcode);
        }
    printf("af=%04X, bc=%04X, de=%04X, hl=%04X, pc=%04X, sp=%04X, clk=%X\n", af->all, bc->all, de->all, hl->all, pc->all, sp->all, clock);

        print_ram(0x0, 0x10);
    print_ram(0x100, 0x8);
    print_ram(0x2000, 0x8);
    print_ram(0x4000, 0x8);
    print_ram(0x8000, 0x8);
    print_ram(0x9800, 0x8);
    print_ram(0xFE00, 0x10);
        print_ram(0xFF00, 0x10);
        print_ram(0xFF40, 0x11);
    print_ram(0xFF70, 0x10);
    print_ram(0xFF80, 0x80);
    printf("\n");
}

void debug_show_reg_ram(bool is_cb_cmd, eu8 opcode, eu8 clock) {
    set_debug_flag();
    if (g_debug) {
        show_reg_ram(is_cb_cmd, opcode, clock);
    }
}

void debug_show_pixels_table(eu8 frame_buffer[SCREEN_HEIGHT][SCREEN_WIDTH]) {
    for (eu8 y = 0; y < SCREEN_HEIGHT; y++) {
        //PRINTF_DEBUG_NOCRLF("\n");
        for (eu8 x = 0; x < SCREEN_WIDTH; x++) {
            //PRINTF_DEBUG_NOCRLF("%01X ", frame_buffer[y][x]);
        }
    }
}

void stop_cmd_cnt(eu32 cmdCnt) {
    if (g_cmdCnt == cmdCnt) {
        PRINTF_ALWAYS("\n");
    }
}