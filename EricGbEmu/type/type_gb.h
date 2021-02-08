#pragma once

typedef eu16 RamAddr;

typedef struct {
    eu8 p1;
    eu8 sb;
    eu8 sc;
    eu8 :8;

    //0xFF04
    eu8 div;

    eu8 tima;
    eu8 tma;
    eu8 tac;
    eu8 : 8;
    eu8 : 8;
    eu8 : 8;
    eu8 : 8;
    eu8 : 8;
    eu8 : 8;
    eu8 : 8;

    //0xFF0F
    eu8 int_flag;

    //FF10
    eu8 nr[0x20];

    //FF30
    eu8 wave_pattern_ram[0x10];

    //FF40
    eu8 lcd[0x0B];

    //FF4c
    eu32: 32;

    //FF50
    eu8 boot_rom_disable;

    //FF51
    eu8 unused[0x2F];

    //FF80
    eu8 high_ram[0x7F];

    //FFFF: Interrupt Enable (R/W)
    eu8 ie;

}ZeroPage;
ERIC_GEN_POINTER_TYPE(ZeroPage);