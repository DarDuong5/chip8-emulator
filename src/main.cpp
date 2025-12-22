#include <stdio.h>
#include <iostream>

#include "Tests/test_instructions.hpp"
#include "Tests/test_chip8.hpp"

int main() {
    RUN_ALL_OPCODE_TESTS();
    RUN_ALL_CHIP8_TESTS();
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
    -o output/main

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