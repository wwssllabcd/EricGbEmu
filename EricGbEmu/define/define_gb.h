#pragma once

#define GB_RAM_SIZE (_64K)

#define TILE_BYTES (16)

#define TILE_X_PX (8)
#define TILE_Y_PX  (8)


#define SCREEN_WIDTH (160)
#define SCREEN_HEIGHT (144)

#define BG_MAP_PIXEL_SIZE  (256)
#define TILES_PER_LINE (32)


// ----- video -----

#define CLOCKS_PER_HBLANK (204)         // Mode 0
#define CLOCKS_PER_SCANLINE_OAM (80)    // Mode 2
#define CLOCKS_PER_SCANLINE_VRAM (172)  // Mode 3
#define CLOCKS_PER_SCANLINE (CLOCKS_PER_HBLANK + CLOCKS_PER_SCANLINE_OAM + CLOCKS_PER_SCANLINE_VRAM)

#define STAT_HBLANK_PERIOD (0)
#define STAT_VBLANK_PERIOD (1)
#define STAT_SCAN_OAM_RAM  (2)
#define STAT_TRANSFER_DATA_TO_LCD_DRIVE (3)