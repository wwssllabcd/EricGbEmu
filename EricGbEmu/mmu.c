

#include "mmu.h"
#include "header.h"


eu8 g_ram[GB_RAM_SIZE] = { 0 };

eu8_p get_ram_ptr(RamAddr address) {
    return (eu8_p)&g_ram[address];
}

eu8 get_ram(RamAddr address) {
    return (*get_ram_ptr(address));
}

void set_ram(RamAddr address, eu8 val) {
    (*get_ram_ptr(address)) = val;
}

void init_mmu(eu8_p rom) {
    mem_cpy(g_ram + GAME_ROM_START_ADDR, rom, GAME_ROM_LENGTH);

    set_ram(0xFF00, 0x3F);
    set_ram(0xFF02, 0xFF);
}