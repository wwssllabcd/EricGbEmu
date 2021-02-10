#pragma once
#include "header.h"



typedef union {
    eu8 all;
    struct {
        eu8 tile_px : 3;
        eu8 tile_id : 5;
    };
}ScrollPx;

typedef union {
    eu8 all;
    struct {
        //This selects the shade of grays to use for the background(BG)& window pixels.
        //Since each pixel uses 2 bits, the corresponding shade will be selected from here.
        eu8 data_for_dot_data_00 : 2;
        eu8 data_for_dot_data_01 : 2;
        eu8 data_for_dot_data_10 : 2;
        eu8 data_for_dot_data_11 : 2;
    };
}Palette;
ERIC_GEN_POINTER_TYPE(Palette);

typedef struct {

    //FF40
    union {
        eu8 all;
        struct {
            //Bit 0
            //0: off, 1 : on

            eu8 bg_and_window_display : 1;

            //Bit 1
            //0: off, 1 : on
            eu8 obj_display : 1;

            //Bit 2
            //0: 8*8, 1: 8 * 16 (width * height)
            eu8 obj_size : 1;

            //Bit 3
            //0: $9800-$9BFF, 1: $9C00 - $9FFF
            eu8 bg_tile_map_display_select : 1;

            //Bit 4
            //0: $8800-$97FF, 1: $8000 - $8FFF < -Same area as OBJ
            eu8 bg_and_window_tile_data_select : 1;

            //Bit 5
            //0: off, 1 : on
            eu8 window_dispaly : 1;

            //Bit 6
            //0: $9800-$9BFF, 1: $9C00 - $9FFF
            eu8 window_tile_map_display_select : 1;

            //Bit 7
            //0: Stop completely(no picture on screen), 1 : operation
            eu8 lcd_control_operation : 1;
        };
    }lcdc;

    //FF41
    union {
        eu8 all;
        struct {
            //Bit[0:1]
            //Mode 00: When the flag is 00 it is the H - Blank period and the CPU can access the display RAM($8000 - $9FFF).
            //Mode 01: When the flag is 01 it is the V - Blank period and the CPU can access the display RAM($8000 - $9FFF).
            //Mode 10: When the flag is 10 then the OAM is being used($FE00 - $FE9F).The CPU cannot access the OAM during this period
            //Mode 11: When the flag is 11 both the OAM and display RAM are being used.The CPU cannot access either during this period.
            eu8 mode_flag : 2;

            //Bit 2, 0: LYC not equal to LCDC LY, 1: LYC = LCDC LY
            eu8 coincidence_flag : 1;

            //Bit 3, HBlank, 0: Non Selection, 1 : Selection
            eu8 mode_00 : 1;

            //Bit 4, VBlank
            eu8 mode_01 : 1;
            
            //Bit 5, OAM used 
            eu8 mode_10 : 1;

            // Bit 6: LYC=LY Coincidence (Selectable)
            eu8 ly_c : 1;
            eu8 : 1;
        };
    }stat;

    //FF42: 8 Bit value $00-$FF to scroll BG Y screen position.
    eu8 scy;

    //FF43: 8 Bit value $00-$FF to scroll BG X screen position.
    eu8 scx;

    //FF44: The LY indicates the vertical line to which the present data is transferred to the LCD Driver.
    //    The LY can take on any value between 0 through 153. 
    //    The values between 144 and 153 indicate the V - Blank period.
    //    Writing will reset the counter.
    eu8 ly;

    //FF45: LY Compare  (R/W)，當draw line(也就是 FF00) 到達lyc 所指定的行數時，就會觸發 int
    //這樣可以讓畫面畫到一半的時候，能通知cpu介入，去做不同的事情
    eu8 lyc;

    //FF46: DMA Transfer and Start Address (W)
    eu8 dma;

    //FF47: BG & Window Palette Data  (R/W)
    Palette bgp;

    //FF48: Object Palette 0 Data (R/W)
    Palette obp0;

    //FF49: Object Palette 1 Data (R/W)
    Palette obp1;

    //FF4A: Window Y Position  (R/W),  0 <= WY <= 143
    eu8 wy;

    //FF4B: Window X Position  (R/W),  0 <= WX <= 166
    // WX is offset from absolute screen coordinates by 7
    eu8 wx;
}LcdRegister;
ERIC_GEN_POINTER_TYPE(LcdRegister);


typedef union {
    eu8 all;
    struct {
        //Bit 0
        eu8 vblank : 1;
        //Bit 1
        eu8 lcdc : 1;
        //Bit 2
        eu8 timer_overflow : 1;
        //Bit 3
        eu8 serial_io_transfer_complete : 1;
        //Bit 4, Transition from High to Low of Pin number P10 - P13
        eu8 trans_from_high_to_Low_of_pin_number : 1;
        eu8 : 3;
    };
}Interrupt;

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
    Interrupt int_flag;

    //FF10
    eu8 nr[0x20];

    //FF30
    eu8 wave_pattern_ram[0x10];

    //FF40
    LcdRegister lcd;

    //FF4c
    eu32: 32;

    //FF50
    eu8 boot_rom_disable;

    //FF51
    eu8 unused[0x2F];

    //FF80
    eu8 high_ram[0x7F];

    //FFFF: Interrupt Enable (R/W)
    Interrupt ie;

}ZeroPage;
ERIC_GEN_POINTER_TYPE(ZeroPage);

typedef struct {
    eu8 y;
    eu8 x;
    
    //Byte2: Pattern number 0-255 
    //(Unlike some tile numbers, sprite pattern numbers are unsigned. LSB is ignored(treated as 0) in 8x16 mode.)
    eu8 pattern_num;

    union {
        eu8 all;
        struct {
            eu8 : 4;
            //Bit 4
            //Sprite colors are taken from OBJ1PAL if this bit is set to 1 and from OBJ0PAL otherwise
            eu8 palette_number : 1;

            //Bit 5
            //Sprite pattern is flipped horizontally if this bit is set to 1.
            eu8 flap_x : 1;

            //Bit 6
            //Sprite pattern is flipped vertically   if this bit is set to 1.
            eu8 flap_y : 1;

            //Bit 7
            //0: sprite is displayed on top of background & window
            //1: sprite will be hidden behind colors 1, 2, and 3 of the background & window
            eu8 priority : 1;
        };
    }flags;
}Sprite;
ERIC_GEN_POINTER_TYPE(Sprite);

#define TOTAL_SPRITE_CNT (40)
typedef struct {
    Sprite spriteMap[TOTAL_SPRITE_CNT];
}SpriteMap;
ERIC_GEN_POINTER_TYPE(SpriteMap);


typedef struct {
    eu8 byte0;
    eu8 byte1;
}TileLine;
ERIC_GEN_POINTER_TYPE(TileLine);
#define TILE_LINE_CNT     (0x8)
#define TILE_PATTERN_SIZE (TILE_LINE_CNT*2)


typedef struct {
    TileLine line_map[TILE_LINE_CNT];
}TilePattern;
ERIC_GEN_POINTER_TYPE(TilePattern);

#define TOTAL_TILE_PATTERN_CNT (256)
typedef struct {
    TilePattern pattern_map[TOTAL_TILE_PATTERN_CNT];
}TilePatternMap;
ERIC_GEN_POINTER_TYPE(TilePatternMap);

#define TILE_CNT_OF_SCREEN (32)
#define TOTAL_TILE_CNT_OF_SCREEN (TILE_CNT_OF_SCREEN*TILE_CNT_OF_SCREEN)
typedef struct {
    union {
        eu8 map[TOTAL_TILE_CNT_OF_SCREEN];
        eu8 map_xy[TILE_CNT_OF_SCREEN][TILE_CNT_OF_SCREEN];
    };
}TileIdMap;
ERIC_GEN_POINTER_TYPE(TileIdMap);

