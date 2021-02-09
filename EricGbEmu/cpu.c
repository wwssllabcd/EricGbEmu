

#include "Cpu.h"
#include "header.h"
#include "mmu.h"
#include "opcode/opcode_map.h"

Cpu g_cpu = {
    .af = 0,
    .bc = 0,
    .de = 0,
    .hl = 0,
    .sp = 0,
    .pc = 0,

    .halt = false,
    .running = true,
    .enable_interrupt = false,

    .clock_cnt = 0,
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

void set_z(bool val) {
    flags->z = SET_FLAG(val);
}

void set_h(bool val) {
    flags->h = SET_FLAG(val);
}

void set_n(bool val) {
    flags->n = SET_FLAG(val);
}

void set_c(bool val) {
    flags->c = SET_FLAG(val);
}

void disable_halt() {
    g_cpu.halt = false;
}

void enable_halt() {
    g_cpu.halt = true;
}

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

eu8 fetch(void) {
    eu8 val = get_ram(REG_PC);
    INC_REG(pc);
    return val;
}

eu16 fetch_word() {
    eu16 val = 0;
    val |= fetch();
    val |= fetch() << 8;
    return val;
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
    return 1;
}

eu8 cpu_tick() {
    if (g_cpu.halt) {
        return 1;
    }
    return execute_opcode();
}

void tick() {
    
    cpu_tick();

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
