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


int main(int argc, char* argv[]) {

    /* TESTS
    RUN_ALL_OPCODE_TESTS();
    RUN_ALL_CHIP8_TESTS();

    std::cout << "All tests passed successfully!" << std::endl;
    */

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
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Roughly 60Hz

        processInput(&chip8);
        while (chip8.isPaused && chip8.isRunning) {
            processInput(&chip8);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    kill(&sdlContext);
    std::cout << "Emulation ended." << std::endl;

    return 0;
}


/*
How to compile and run:

Bash
g++ -Wall -Wextra -g3 \
    src/Chip8/chip8.cpp \
    src/Display/display.cpp \
    src/Instructions/instructions.cpp \
    src/Keypad/keypad.cpp \
    src/Tests/test_instructions.cpp \
    src/Tests/test_chip8.cpp \
    src/main.cpp \
    -o output/chip8 \
    $(sdl2-config --cflags --libs)

Powershell
g++ -Wall -Wextra -g3 
src/Chip8/chip8.cpp 
src/Display/display.cpp 
src/Instructions/instructions.cpp 
src/Keypad/keypad.cpp 
src/Tests/test_instructions.cpp 
src/Tests/test_chip8.cpp
.\src\main.cpp 
-o output/main.exe
*/