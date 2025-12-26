#include "display.hpp"

SDLContext initSDL() {
    SDLContext context{};

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    context.window = SDL_CreateWindow(
        "Chip8 Emulator", 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 
        DISPLAY_WIDTH * X_SCALE, 
        DISPLAY_HEIGHT * Y_SCALE, 
        SDL_WINDOW_SHOWN
    );

    if (!context.window) {
        std::cout << "Failed to create a window! Error: " << SDL_GetError() << std::endl;
        kill(&context);
        exit(EXIT_FAILURE);
    }
    
    context.renderer = SDL_CreateRenderer(
        context.window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (!context.renderer) {
        std::cout << "Failed to create a renderer! Error: " << SDL_GetError() << std::endl;
        kill(&context);
        exit(EXIT_FAILURE);
    }

    SDL_RenderSetScale(context.renderer, (float) X_SCALE, (float) Y_SCALE);

    return context;
}

void drawSDL(SDLContext* context, Chip8& chip8) {
    SDL_SetRenderDrawColor(context->renderer, 0, 0, 0, 255);
    SDL_RenderClear(context->renderer);
    SDL_SetRenderDrawColor(context->renderer, 255, 255, 255, 255);

    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
        for (int x = 0; x < DISPLAY_WIDTH; x++) {
            SDL_Rect rect;
            rect.x = x;
            rect.y = y;
            rect.w = 1;
            rect.h = 1;
            if (chip8.display[x][y]) {
                SDL_SetRenderDrawColor(context->renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(context->renderer, &rect);
            } else {
                SDL_SetRenderDrawColor(context->renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(context->renderer, &rect);
            }
        }
    }

    SDL_RenderPresent(context->renderer);
}

// Quit
void kill(SDLContext* context) {
    SDL_DestroyRenderer(context->renderer);
    SDL_DestroyWindow(context->window);
    SDL_Quit();
}