#pragma once
#include "header.h"

#define SDL_PIXEL_SIZE (2)

void draw_sdl2(eu8 frame_buffer[SCREEN_HEIGHT][SCREEN_WIDTH]);
void init_sdl(char* title, eu32 width, eu32 height);
