

#include "video.h"
#include "mmu.h"
#include "adapter_sdl.h"
#include "debug.h"
#include "cpu.h"
#include <stdio.h>

enum  {
    ACCESS_OAM,
    ACCESS_VRAM,
    HBLANK,
    VBLANK,
};

eu8 g_curMode = 0;
eu32 g_videoClock = 0;
eu8 g_screenFrameBuffer[SCREEN_HEIGHT][SCREEN_WIDTH];

void draw() {
    draw_sdl2(g_screenFrameBuffer);
}

eu8 get_pixel_data(eu8 byte_0, eu8 byte_1, eu8 px_offset) {
    return (CHECK_BIT(byte_1, 7 - px_offset) << 1) | (CHECK_BIT(byte_0, 7 - px_offset));
}

TilePatternMap_p get_tile_data_table_bg_window() {
    return get_tile_data_table(LCD_CTRL.bg_and_window_tile_data_select);
}

TileIdMap_p get_bg_tile_id_map() {
    return get_tile_id_map(LCD_CTRL.bg_tile_map_display_select);
}

TileIdMap_p get_window_tile_id_map() {
    return get_tile_id_map(LCD_CTRL.window_tile_map_display_select);
}

void check_and_set_lyc_flag() {
    LCD_STAT.coincidence_flag = (LCD.ly == LCD.lyc);
    if (LCD_STAT.ly_c && LCD_STAT.coincidence_flag) {
        IE.lcdc = 1;
    }
}

eu8 get_palette(Palette_sp p, eu8 num) {
    if (num == 0) {
        return p->data_for_dot_data_00;
    }
    if (num == 1) {
        return p->data_for_dot_data_01;
    }
    if (num == 2) {
        return p->data_for_dot_data_10;
    }
    if (num == 3) {
        return p->data_for_dot_data_11;
    }

    ASSERT_CODE(0, "wrong palette num=%X", num);
    return NULL_8;
}

eu8 get_bg_palette(eu8 num) {
    return get_palette(&LCD.bgp, num);
}

eu8 get_sprite_palette(eu8 select, eu8 num) {
    if (select) {
        return get_palette(&LCD.obp1, num);
    }
    return get_palette(&LCD.obp0, num);
}

bool is_pixel_on_screen(eu32 x, eu32 y) {
    if (x >= SCREEN_WIDTH) {
        return false;
    }
    if (y >= SCREEN_HEIGHT) {
        return false;
    }
    return true;
}

void write_screen_frame_buffer(eu8 x, eu8 y, eu8 color) {
    if (x >= SCREEN_WIDTH) {
        ASSERT_CODE(0, "screen_x ofb =%X", x);
    }
    if (y >= SCREEN_HEIGHT) {
        ASSERT_CODE(0, "screen_y ofb =%X", y);
    }
    g_screenFrameBuffer[y][x] = color;
}

void draw_bg_window_line(eu8 screen_x, eu8 screen_y, ScrollPx scroll_x, ScrollPx scroll_y, TileIdMap_sp screenTileIdMap) {
    TilePatternMap_sp tileDataTable = get_tile_data_table_bg_window();
    eu8 tile_id = screenTileIdMap->map_xy[scroll_y.tile_id][scroll_x.tile_id];

    if (!LCD_CTRL.bg_and_window_tile_data_select) {
        tile_id -= 0x80;
    }

    TileLine_sp tileLine = &tileDataTable->pattern_map[tile_id].line_map[scroll_y.tile_px];
    write_screen_frame_buffer(screen_x, screen_y, get_bg_palette(get_pixel_data(tileLine->byte0, tileLine->byte1, scroll_x.tile_px)));
}

void draw_window_line(eu8 screen_y) {
    eu8 scrolled_x = LCD.wx - 7;
    eu8 scrolled_y = screen_y - LCD.wy;

    if (scrolled_y >= SCREEN_HEIGHT) { return; }

    TileIdMap_usp screenTileIdMap = get_window_tile_id_map();

    for (eu8 screen_x = 0; screen_x < SCREEN_WIDTH; screen_x++) {
        ScrollPx scroll_x = { .all = scrolled_x + screen_x };
        ScrollPx scroll_y = { .all = scrolled_y };
        draw_bg_window_line(screen_x, screen_y, scroll_x, scroll_y, screenTileIdMap);
    }
}

void get_bg_line_data(eu8 screen_y) {
    eu8 scrolled_x = LCD.scx;
    eu8 scrolled_y = screen_y + LCD.scy;

    TileIdMap_usp screenTileIdMap = get_bg_tile_id_map();

    for (eu8 screen_x = 0; screen_x < SCREEN_WIDTH; screen_x++) {
        // we need to roll back to 0 when scrolled_x > 256
        ScrollPx scroll_x = {.all = (scrolled_x + screen_x) % BG_MAP_PIXEL_SIZE};
        ScrollPx scroll_y = {.all = (scrolled_y) % BG_MAP_PIXEL_SIZE};

        draw_bg_window_line(screen_x, screen_y, scroll_x, scroll_y, screenTileIdMap);
    }
}

void draw_sprite(eu8 spriteNum) {
    Sprite_p sprite = GET_SPRITE_PTR(spriteNum);
    if (sprite->x == 0 || sprite->x >= 168) {
        return;
    }
    if (sprite->y == 0 || sprite->y >= 160) {
        return;
    }

    //PRINTF_DEBUG("write_sprites num=%X", spriteNum);

    // sprite always use 0x8000
    TilePatternMap_p tilePatternMap = get_tile_data_table(1);

    for (eu8 oam = 0; oam < (LCD_CTRL.obj_size+1); oam++) {
        TilePattern_p tile = &tilePatternMap->pattern_map[sprite->pattern_num + oam];

        eu32 start_x = sprite->x - 8;
        eu32 start_y = sprite->y - 16 + (oam * TILE_Y_PX);

        for (eu8 y = 0; y < TILE_Y_PX; y++) {
            TileLine_p tile_line = &tile->line_map[y];
            for (eu8 x = 0; x < TILE_X_PX; x++) {
                if (!is_pixel_on_screen(start_x + x, start_y + y)) {
                    continue;
                }
                if (sprite->flags.priority) {
                    continue;
                }

                eu8 target_px_x = !sprite->flags.flap_x ? x : TILE_X_PX - x - 1;
                eu8 target_px_y = !sprite->flags.flap_y ? y : TILE_Y_PX - y - 1;
                eu8 screen_x = (eu8)(start_x + target_px_x);
                eu8 screen_y = (eu8)(start_y + target_px_y);


                eu8 px_data = get_pixel_data(tile_line->byte0, tile_line->byte1, target_px_x);
                // 0 is transparent
                if (px_data == 0) {
                    continue;
                }

                eu8 color = get_sprite_palette(sprite->flags.palette_number, px_data);
                write_screen_frame_buffer(screen_x, screen_y, color);
            }
        }
    }
}

void write_sprites() {
    if (!LCD_CTRL.obj_display) {
        return;
    }

    for (eu8 sprite_n = 0; sprite_n < TOTAL_SPRITE_CNT; sprite_n++) {
        draw_sprite(sprite_n);
    }
}

void write_scan_line(eu8 curLine) {
    if (!LCD_CTRL.lcd_control_operation) {
        return;
    }

    if (LCD_CTRL.bg_and_window_display) {
        get_bg_line_data(curLine);
    }

    if (LCD_CTRL.window_dispaly) {
        draw_window_line(curLine);
    }
}

void video_tick(eu8 clock) {
    g_videoClock += clock;

    switch (g_curMode) {
        case ACCESS_OAM:
            if (g_videoClock >= CLOCKS_PER_SCANLINE_OAM) {
                g_videoClock = g_videoClock % CLOCKS_PER_SCANLINE_OAM;
                LCD_STAT.mode_flag = STAT_TRANSFER_DATA_TO_LCD_DRIVE;
                g_curMode = ACCESS_VRAM;
            }
            break;
        case ACCESS_VRAM:
            if (g_videoClock >= CLOCKS_PER_SCANLINE_VRAM) {
                g_videoClock = g_videoClock % CLOCKS_PER_SCANLINE_VRAM;

                // if it is H-bank period
                if (LCD_STAT.mode_00) {
                    IE.lcdc = 1;
                }
                check_and_set_lyc_flag();
                LCD_STAT.mode_flag = STAT_HBLANK_PERIOD;

                g_curMode = HBLANK;
            }
            break;
        case HBLANK:
            if (g_videoClock >= CLOCKS_PER_HBLANK) {
                g_videoClock = g_videoClock % CLOCKS_PER_HBLANK;

                write_scan_line(LCD.ly);
                LCD.ly++;
                
                if (LCD.ly < 144) {
                    LCD_STAT.mode_flag = STAT_SCAN_OAM_RAM;
                    g_curMode = ACCESS_OAM;
                } else {
                    LCD_STAT.mode_flag = STAT_VBLANK_PERIOD;
                    IF.vblank = 1;
                    g_curMode = VBLANK;
                }
            }
            break;
        case VBLANK:
            if (g_videoClock >= CLOCKS_PER_SCANLINE) {
                g_videoClock = g_videoClock % CLOCKS_PER_SCANLINE;
                LCD.ly++;
                if (LCD.ly >= 154) {
                    write_sprites();
                    draw();

                    LCD.ly = 0;
                    LCD_STAT.mode_flag = STAT_SCAN_OAM_RAM;

                    g_curMode = ACCESS_OAM;
                }
            }
            break;
    };

    if (g_curMode == ACCESS_OAM) {
        if (LCD_STAT.mode_flag != STAT_SCAN_OAM_RAM) {
            printf("\nwrong mode, ACCESS_OAM, but lcd=%X", LCD_STAT.mode_flag);
        }
    }
    if (g_curMode == ACCESS_VRAM) {
        if (LCD_STAT.mode_flag != STAT_TRANSFER_DATA_TO_LCD_DRIVE) {
            printf("\nwrong mode, ACCESS_VRAM, but lcd=%X", LCD_STAT.mode_flag);
        }
    }
    if (g_curMode == HBLANK) {
        if (LCD_STAT.mode_flag != STAT_HBLANK_PERIOD) {
            printf("\nwrong mode, HBLANK, but lcd=%X", LCD_STAT.mode_flag);
        }
    }
    if (g_curMode == VBLANK) {
        if (LCD_STAT.mode_flag != STAT_VBLANK_PERIOD) {
            printf("\nwrong mode, VBLANK, but lcd=%X", LCD_STAT.mode_flag);
        }
    }

    PRINTF_DEBUG("TC=%X,VC=%X,VM=%X, ", g_cpu.clockCnt, g_videoClock, LCD_STAT.mode_flag);
}