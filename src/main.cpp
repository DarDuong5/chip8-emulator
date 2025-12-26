#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "Tests/test_instructions.hpp"
#include "Tests/test_chip8.hpp"
#include "Display/display.hpp"
#include "Keypad/keypad.hpp"
#include <fstream>
#include <string>



#define CPU_CLOCK_SPEED 500
#define FRAME_RATE 60
#define TIMER_RATE 60

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <path_to_rom>" << std::endl;
        exit(EXIT_FAILURE);
    }

    Chip8 chip8;
    const char* rom = argv[1];

    if (!rom) {
        std::cout << "ROM path not provided." << std::endl;
        std::cout << "Usage: " << argv[0] << " <path_to_rom>" << std::endl;
        exit(EXIT_FAILURE);
    }

    chip8.romPath = rom;
    chip8.loadROM();

    SDLContext sdlContext = initSDL();

    while (chip8.isRunning) {
        decodeAndExecuteInstructions(&chip8);
        drawSDL(&sdlContext, chip8);
        updateTimers(&chip8);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        processInput(&chip8);
        while (chip8.isPaused && chip8.isRunning) {
            processInput(&chip8);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    kill(&sdlContext);
    std::cout << "Emulation ended." << std::endl;

    return 0;
}