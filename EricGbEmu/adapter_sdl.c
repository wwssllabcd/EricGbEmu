
#include "adapter_sdl.h"
#include <SDL.h>
#include "cpu.h"

#define NULL_PTR (0)

SDL_Window* g_window;
SDL_Renderer* g_renderer;
SDL_Texture* g_texture;
uint32_t* g_sdl_pixels;

eu32 get_real_color(eu8 pixel_color) {
    // for compile error
    eu8 r = 0;
    eu8 g = 0;
    eu8 b = 0;

    switch (pixel_color) {
        case 0:
            r = g = b = 255;
            break;  // white
        case 1:
            r = g = b = 170;
            break;
        case 2:
            r = g = b = 85;
            break;
        case 3:
            r = g = b = 0;
            break;  // black
        default:
            ASSERT_CODE(0, "Wrong pixel color = %X", pixel_color);
    }

    return (r << 16) | (g << 8) | (b << 0);
}

void set_pixel(eu32 x, eu32 y, eu8 color) {
    g_sdl_pixels[SCREEN_WIDTH * SDL_PIXEL_SIZE * y + x] = get_real_color(color);
}

void set_large_pixels(eu8 x, eu8 y, eu8 color) {
    for (eu8 w = 0; w < SDL_PIXEL_SIZE; w++) {
        for (eu8 h = 0; h < SDL_PIXEL_SIZE; h++) {
            eu32 fin_x = x * SDL_PIXEL_SIZE + w;
            eu32 fin_y = y * SDL_PIXEL_SIZE + h;
            set_pixel(fin_x, fin_y, color);
        }
    }
}

void set_pixels(eu8 frame_buffer[SCREEN_HEIGHT][SCREEN_WIDTH]) {
    for (eu8 y = 0; y < SCREEN_HEIGHT; y++) {
        for (eu8 x = 0; x < SCREEN_WIDTH; x++) {
            set_large_pixels(x, y, frame_buffer[y][x]);
        }
    }
}

void process_events() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.repeat == true) {
                    break;
                }
                break;
            case SDL_KEYUP:
                if (event.key.repeat == true) {
                    break;
                }
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                    g_cpu.running = true;
                }
                break;
            case SDL_QUIT:
                g_cpu.running = false;
                break;
        }
    }
}

void draw_sdl2(eu8 frame_buffer[SCREEN_HEIGHT][SCREEN_WIDTH]) {
    process_events();

    SDL_RenderClear(g_renderer);

    void* pixels_ptr;
    int pitch;

    SDL_LockTexture(g_texture, NULL_PTR, &pixels_ptr, &pitch);

    g_sdl_pixels =(uint32_t*)(pixels_ptr);

    set_pixels(frame_buffer);

    SDL_UnlockTexture(g_texture);
    SDL_RenderCopy(g_renderer, g_texture, NULL_PTR, NULL_PTR);
    SDL_RenderPresent(g_renderer);
}

void init_sdl(char* title, eu32 width, eu32 height) {
    SDL_Init(SDL_INIT_VIDEO);

    g_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

    if (g_window == NULL_PTR) {
        ASSERT_CODE(0, "Failed to initialise SD=%X", g_window);
    }
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    g_texture = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
}