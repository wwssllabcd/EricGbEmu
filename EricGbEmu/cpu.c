

#include "Cpu.h"
#include "header.h"
#include "mmu.h"
#include "opcode/opcode_map.h"
#include "cpu_cycle.h"
#include "video.h"
#include "debug.h"

// V - Blank               1         $0040
// LCDC Status             2         $0048 - Modes 0, 1, 2, LYC = LY coincide(selectable)
// Timer Overflow          3         $0050
// Serial Transfer         4         $0058 - when transfer is complete
// Hi - Lo of P10 - P13    5         $0060
#define INT_VBLANK (0x40)
#define INT_LCDC_STATUS (0x48)
#define INT_TIMER (0x50)
#define INT_SERIAL (0x58)
#define INT_JOY_PAD (0x60)

bool g_is_branch = false;

Cpu g_cpu = {
    .af = 0,
    .bc = 0,
    .de = 0,
    .hl = 0,
    .sp = 0,
    .pc = 0,

    .halt = false,
    .running = true,
    .enableInterrupt = false,

    .clockCnt = 0,
};

WordReg_p af = &g_cpu.af;
WordReg_p bc = &g_cpu.bc;
WordReg_p de = &g_cpu.de;
WordReg_p hl = &g_cpu.hl;
WordReg_p sp = &g_cpu.sp;
WordReg_p pc = &g_cpu.pc;

ByteReg_p a = &g_cpu.a;
FlagReg_p flags = &g_cpu.f;
ByteReg_p b = &g_cpu.b;
ByteReg_p c = &g_cpu.c;
ByteReg_p d = &g_cpu.d;
ByteReg_p e = &g_cpu.e;
ByteReg_p h = &g_cpu.h;
ByteReg_p l = &g_cpu.l;

void stack_push(WordReg_p reg) {
    DEC_REG(sp);
    set_ram(REG_SP, REG_VAL(REG_HIGH(reg)));
    DEC_REG(sp);
    set_ram(REG_SP, REG_VAL(REG_LOW(reg)));
}

void stack_pop(WordReg_p reg) {
    REG_VAL(REG_LOW(reg)) = get_ram(REG_SP);
    INC_REG(sp);
    REG_VAL(REG_HIGH(reg)) = get_ram(REG_SP);
    INC_REG(sp);
}

void set_z(bool value) {
    flags->z = SET_FLAG(value);
}

void set_h(bool value) {
    flags->h = SET_FLAG(value);
}

void set_n(bool value) {
    flags->n = SET_FLAG(value);
}

void set_c(bool value) {
    flags->c = SET_FLAG(value);
}

eu8 increase_pc(eu8 value) {
    INC_REG(pc);
    return value;
}

eu8 fetch(void) {
    return increase_pc(get_ram(REG_PC));
}

eu16 fetch_word() {
    eu16 value = 0;
    value |= fetch();
    value |= fetch() << 8;
    return value;
}

bool setup_int(eu8 bit, eu8 jumpPc, eu8 curInts) {
    if (curInts & TO_BIT_NUM(bit)) {
        g_zeroPage->int_flag.all &= (~TO_BIT_NUM(bit));
        REG_PC = jumpPc;
        g_cpu.enableInterrupt = false;
        return true;
    }
    return false;
}

void disable_halt() {
    g_cpu.halt = false;
}

void enable_halt() {
    g_cpu.halt = true;
}

void handle_interrupt() {
    
    //PRINTF_DEBUG("int_enable=%X, ie=%X, if=%X\n", g_cpu.enableInterrupt, g_zeroPage->ie.all, g_zeroPage->int_flag.all);
    
    if (!g_cpu.enableInterrupt) {
        return;
    }

    Interrupt interrupts;
    interrupts.all = (g_zeroPage->int_flag.all & g_zeroPage->ie.all);
    if (!interrupts.all) {
        return;
    }

    disable_halt();
    stack_push(pc);
 
    if (setup_int(0, INT_VBLANK, interrupts.all)) {
        return;
    }
    if (setup_int(1, INT_LCDC_STATUS, interrupts.all)) {
        return;
    }
    if (setup_int(2, INT_TIMER, interrupts.all)) {
        return;
    }
    if (setup_int(3, INT_SERIAL, interrupts.all)) {
        return;
    }
    if (setup_int(4, INT_JOY_PAD, interrupts.all)) {
        return;
    }
}

eu8 execute_opcode() {
    eu8 opcode = fetch();
    opcode_fun_usp op_map = g_opcode_fun_map;
    bool is_cb_cmd = false;

    if (opcode == PREFIX_CMD) {
        opcode = fetch();
        op_map = g_opcode_cb_fun_map;
        is_cb_cmd = true;
    }

    op_map[opcode]();
    eu8 clock = get_op_cycle(is_cb_cmd, opcode);

    debug_show_reg_ram(is_cb_cmd, opcode, clock);

    g_is_branch = false;
    g_cmd_cnt++;

    return clock;
}

eu8 cpu_tick() {
    handle_interrupt();
    if ( g_cpu.halt ) {
        return 1;
    }

    return execute_opcode();
}

void timer_tick(eu8 clock) {
    g_zeroPage->div += clock;
}

void tick() {
    eu8 clock = cpu_tick();




    video_tick(clock);
    timer_tick(clock);
}

void run_cpu() {
    while (g_cpu.running) {
        tick();
    }
}

void power_on_cpu(eu8_p rom) {
    init_mmu(rom);
    run_cpu();
}
