
#include <stdio.h>
#include <Windows.h>
#include <SDL.h>
#include "header.h"
#include "adapter_sdl.h"


int main(int argc, char* argv[])
{
    printf("start\n");
    
    init_sdl("My Gameboy Emulator", SCREEN_WIDTH, SCREEN_WIDTH);
    system("PAUSE");
    SDL_Quit();

    return 0;
}

