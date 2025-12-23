#include "keypad.hpp"

void processInput(Chip8* chip8) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            std::cout << "Program closed, shutting the system off." << std::endl;
            chip8->isRunning = false;
            chip8->isPaused = false;
        }

        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                if (event.key.type == SDL_KEYUP) {
                    continue;
                }
                std::cout << event.key.keysym.sym << " key pressed, shutting off system.." << std::endl;
                chip8->isRunning = false;
                chip8->isPaused = false;
                break;
            case SDLK_SPACE:
                if (event.key.type == SDL_KEYUP) {
                    continue;
                }
                std::cout << event.key.keysym.sym << " key pressed, pausing system.." << std::endl;
                chip8->isPaused ^= 1;
                break;
            case SDLK_RCTRL:
                if (event.key.type == SDL_KEYUP) {
                    continue;
                }
                std::cout << event.key.keysym.sym << " key pressed, restarting system.." << std::endl;
                chip8->initChip8();
                //chip8->loadROM();
                break;
            case SDLK_1: case SDLK_2: case SDLK_3: case SDLK_4: case SDLK_q: case SDLK_w: case SDLK_e: case SDLK_r: case SDLK_a: case SDLK_s:
            case SDLK_d: case SDLK_f: case SDLK_z: case SDLK_x: case SDLK_c: case SDLK_v:
                std::cout << "Key " << event.key.keysym.sym << " was pressed or released." << std::endl;
                if (event.key.type == SDL_KEYUP) {
                    chip8->keyPad[mapKeys[event.key.keysym.sym]] = 0;
                }
                if (event.key.type == SDL_KEYDOWN) {
                    chip8->keyPad[mapKeys[event.key.keysym.sym]] = 1;
                }
                break;
        }
    }
}