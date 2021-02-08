

#include "Cpu.h"
#include "header.h"
#include "mmu.h"

Cpu g_cpu = {
    .af = 0,
    .bc = 0,
    .de = 0,
    .hl = 0,
    .sp = 0,
    .pc = 0,

    .halt = false,
    .running = true,
    .interrupt_occur = false,

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

void tick() {
    g_cpu.running = false;
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
