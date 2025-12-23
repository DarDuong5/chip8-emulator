#include <stdio.h>
#include <iostream>

#include "Tests/test_instructions.hpp"
#include "Tests/test_chip8.hpp"
#include "Display/display.hpp"

int main(int argc, char *argv[]) {
    RUN_ALL_OPCODE_TESTS();
    RUN_ALL_CHIP8_TESTS();

    SDLContext context = initSDL();
    Chip8 chip8{};
    chip8.initChip8();
    chip8.loadROM("./ROMS/test_opcode.ch8");

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        decodeAndExecuteInstructions(&chip8);
        drawSDL(&context, chip8);

        SDL_Delay(2); // slow it down
    }

    kill(&context);

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
    -o output/main \
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