#pragma once


#include "header.h"

eu8_p get_ram_ptr(RamAddr address);
eu8 get_ram(RamAddr address);
void set_ram(RamAddr address, eu8 val);
void init_mmu(eu8_p rom);