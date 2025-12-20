#include <stdio.h>
#include <iostream>

#include "src/Tests/test_instructions.hpp"

int main() {
    test_00E0();
    test_00EE();
    test_1NNN();
    test_2NNN();
    test_3XKK();
    test_4XKK();
    test_5XY0();
    test_6XKK();
    test_7XKK();
    test_8XY4();
    test_8XY6();
    test_8XYE();
    test_ANNN();
    test_CXKK();
    test_DXYN();
    test_FX33();
    test_8XY0();
    test_8XY1();
    test_8XY2();
    test_8XY3();
    test_8XY5();
    test_8XY7();
    test_9XY0();
    test_BNNN();
    test_EX9E();
    test_EXA1();
    test_FX07();
    test_FX0A();
    test_FX15();
    test_FX18();
    test_FX1E();
    test_FX29();
    test_FX55();
    test_FX65();

    std::cout << "\nAll opcode tests passed!" << std::endl;

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
    src/main.cpp \
    -o output/main

Powershell
g++ -Wall -Wextra -g3 src/Chip8/chip8.cpp src/Display/display.cpp src/Instructions/instructions.cpp src/Keypad/keypad.cpp src/Tests/test_instructions.cpp .\src\main.cpp -o output/main.exe
*/