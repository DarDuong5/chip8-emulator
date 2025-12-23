#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "SDL2/SDL.h"
#include <iostream>
#include "../Chip8/chip8.hpp"

#define ON 0xFFFFFFFF
#define OFF 0x00000000
#define X_SCALE 16
#define Y_SCALE 16

class SDLContext {
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

SDLContext initSDL();
void drawSDL(SDLContext* context, Chip8& chip8);
void kill(SDLContext* context);

#endif