#pragma once


#define BOOT_ROM_LENGTH              (0x100)

#define GAME_ROM_START_ADDR          (0)
#define GAME_ROM_LENGTH              (32768)


#define TILE_PATTERN_MAP_0           (0x8000)
#define TILE_PATTERN_MAP_1           (0x8800)

#define TILE_MAP_0                   (0x9800)
#define TILE_MAP_1                   (0x9C00)

// sptire = obj(from Nintando) 
#define SPRITE_MAP_START_ADDR        (0xFE00)
#define ZERO_PAGE                    (0xFF00)


#define IO_P1                        (0xFF00)
#define IO_SERIAL                    (0xFF02)
#define IO_TIMER_MODULE              (0xFF06)
#define IO_TIMER_CTRL                (0xFF07)
#define IO_DMA                       (0xFF46)
#define BOOT_ROM_ENABLE_ADDR         (0xFF50)