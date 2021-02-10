

#include "mmu.h"
#include "header.h"
#include "boot\boot_rom.h"
#include "input.h"

eu8 g_ram[GB_RAM_SIZE] = {0};

SpriteMap_p g_spriteAttrMap = (SpriteMap_p)(g_ram + SPRITE_MAP_START_ADDR);
ZeroPage_p g_zeroPage = (ZeroPage_p)(g_ram + ZERO_PAGE);


void start_hw_dma(eu8 byte) {
    RamAddr base = byte * 0x100;
    for (eu8 i = 0x0; i < 0xA0; i++) {
        RamAddr src = base + i;
        RamAddr dst = SPRITE_MAP_START_ADDR + i;
        set_ram(dst, get_ram(src));
    }
}

eu8_p get_ram_ptr(RamAddr addr) {
    if (addr < BOOT_ROM_LENGTH) {
        if (g_zeroPage->boot_rom_disable == 0) {
            return (eu8_p)&g_bootRom[addr];
        } else {
            return (eu8_p)&g_ram[addr];
        }
    }
    return (eu8_p)&g_ram[addr];
}

eu8 get_ram(RamAddr addr) {
    if (addr == IO_P1) {
        return input_read();
    }

    // fix 0xFF
    if (addr == IO_SERIAL) {
        return 0xFF;
    }
    // DMA, fix 0
    if (addr == IO_DMA) {
        return 0x0;
    }

    return (*get_ram_ptr(addr));
}

void set_ram(RamAddr addr, eu8 value) {

    if (addr == IO_P1) {
        input_write(value);
        return;
    }

    // debug: workaround
    if (addr == IO_TIMER_MODULE) {
        return;
    }

    if (addr == IO_TIMER_CTRL) {
        return;
    }

    // start DMA
    if (addr == IO_DMA) {
        start_hw_dma(value);
        return;
    }

    (*get_ram_ptr(addr)) = value;
}

TilePatternMap_p get_tile_data_table(eu8 select) {
    if (select) {
        return (TilePatternMap_p)(get_ram_ptr(TILE_PATTERN_MAP_0));
    }
    return (TilePatternMap_p)(get_ram_ptr(TILE_PATTERN_MAP_1));
}

TileIdMap_p get_tile_id_map(eu8 select) {
    if (select) {
        return (TileIdMap_p)(g_ram + TILE_MAP_1);
    }
    return (TileIdMap_p)(g_ram + TILE_MAP_0);
}

void init_mmu(eu8_p rom) {
    mem_cpy(g_ram + GAME_ROM_START_ADDR, rom, GAME_ROM_LENGTH);

    set_ram(0xFF00, 0x3F);
    set_ram(0xFF02, 0xFF);
}