
#include "adapter_sdl.h"
#include <SDL.h>

#define NULL_PTR (0)

SDL_Window* g_window;
SDL_Renderer* g_renderer;
SDL_Texture* g_texture;
uint32_t* g_sdl_pixels;

void init_sdl(char* title, eu32 width, eu32 height) {
    SDL_Init(SDL_INIT_VIDEO);

    g_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

    if (g_window == NULL_PTR) {
        ASSERT_CODE(0, "Failed to initialise SD=%X", g_window);
    }
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    g_texture = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
}