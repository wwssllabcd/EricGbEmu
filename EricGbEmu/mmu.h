#pragma once


#include "header.h"


extern ZeroPage_p(g_zero_page);
#define LCD         (g_zero_page->lcd)
#define LCD_CTRL    (g_zero_page->lcd.lcdc)
#define LCD_STAT    (g_zero_page->lcd.stat)
#define IE          (g_zero_page->ie)
#define IF          (g_zero_page->int_flag)



//-------------
eu8_p get_ram_ptr(RamAddr address);
eu8 get_ram(RamAddr address);
void set_ram(RamAddr address, eu8 val);
void init_mmu(eu8_p rom);