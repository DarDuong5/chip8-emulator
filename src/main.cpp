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

    /* TESTS
    RUN_ALL_OPCODE_TESTS();
    RUN_ALL_CHIP8_TESTS();

    std::cout << "All tests passed successfully!" << std::endl;
    */
/*
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
*/
    Chip8 user_chip8;

    const char* rom = argv[1];

    user_chip8.romPath = rom;
    user_chip8.loadROM();
    
    // TODO: Change resolution scaling based on config file
    SDLContext sdlContext = initSDL();

    // CPU clock cycle configuration
    const std::chrono::milliseconds frameDuration(1000 / FRAME_RATE);
    const std::chrono::milliseconds clockDuration(1000 / CPU_CLOCK_SPEED);
    const std::chrono::milliseconds timeDuration(1000 / TIMER_RATE);

    auto lastFrameTime = std::chrono::steady_clock::now();
    auto lastClockTime = std::chrono::steady_clock::now();
    auto lastTimerTime = std::chrono::steady_clock::now();
    
    while(user_chip8.isRunning) {
        auto currentTime = std::chrono::steady_clock::now();

        // CPU Clock updates
        if (currentTime - lastClockTime > clockDuration) {
            decodeAndExecuteInstructions(&user_chip8);
            lastClockTime = currentTime;
        }
        
        // Screen Clock updates
        if (currentTime - lastFrameTime > frameDuration) {
            if (user_chip8.isPaused == false) {
                drawSDL(&sdlContext, user_chip8);
            }
            lastFrameTime = currentTime;
        }

        processInput(&user_chip8);
        while (user_chip8.isPaused && user_chip8.isRunning) {
            processInput(&user_chip8);
        }

        // Timer Clock updates
        if (currentTime - lastTimerTime > timeDuration) {
            updateTimers(&user_chip8);
            lastTimerTime = currentTime;
        }

    }
    
    kill(&sdlContext);
    std::cout << "Finished running";
}