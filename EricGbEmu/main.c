
#include <stdio.h>
#include <SDL.h>
#include "header.h"
#include "adapter_sdl.h"
#include "cpu.h"


int main(int argc, char* argv[])
{
    printf("start\n");
    if (argc == 1) {
        printf("no rom path\n");
        system("PAUSE");
        return 0;
    }

    init_sdl("EricWang Gameboy Emulator", SCREEN_WIDTH * SDL_PIXEL_SIZE, SCREEN_HEIGHT * SDL_PIXEL_SIZE);

    echar_p romFileName = argv[1];

    eu8 rom[GAME_ROM_LENGTH];
    file_read(romFileName, rom, _32K);

    power_on_cpu(rom);

    SDL_Quit();
    return 0;
}

