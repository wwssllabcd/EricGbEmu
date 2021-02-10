#pragma once


#include "header.h"


extern ZeroPage_p(g_zeroPage);
#define LCD         (g_zeroPage->lcd)
#define LCD_CTRL    (g_zeroPage->lcd.lcdc)
#define LCD_STAT    (g_zeroPage->lcd.stat)
#define IE          (g_zeroPage->ie)
#define IF          (g_zeroPage->int_flag)

extern SpriteMap_p g_spriteAttrMap;
#define GET_SPRITE_PTR(NUM) (&g_spriteAttrMap->spriteMap[NUM])



//-------------
eu8_p get_ram_ptr(RamAddr address);
eu8 get_ram(RamAddr address);
void set_ram(RamAddr address, eu8 val);
void init_mmu(eu8_p rom);

TilePatternMap_p get_tile_data_table(eu8 select);
TileIdMap_p get_tile_id_map(eu8 select);