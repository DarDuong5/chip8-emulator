#ifndef TEST_CHIP8_HPP
#define TEST_CHIP8_HPP

#include <cassert>
#include <iostream>

#define LOAD_OPCODE(chip8, op)             \
    do {                                \
        chip8.PC = 0x200;                  \
        chip8.memory[0x200] = (op) >> 8;   \
        chip8.memory[0x201] = (op) & 0xFF; \
    } while (0)

void test_updateTimers();
void test_00E0_DE();
void test_00E0_DE();
void test_00EE_DE();
void test_1NNN_DE();
void test_2NNN_DE();
void test_3XKK_DE();
void test_4XKK_DE();
void test_5XY0_DE();
void test_6XKK_DE();
void test_7XKK_DE();
void test_8XY0_DE();
void test_8XY1_DE();
void test_8XY2_DE();
void test_8XY3_DE();
void test_8XY4_DE();
void test_8XY5_DE();
void test_8XY6_DE();
void test_8XY7_DE();
void test_8XYE_DE();
void test_9XY0_DE();
void test_ANNN_DE();
void test_BNNN_DE();
void test_CXKK_DE();
void test_DXYN_DE();
void test_EX9E_DE();
void test_EXA1_DE();
void test_FX07_DE();
void test_FX0A_DE();
void test_FX15_DE();
void test_FX18_DE();
void test_FX1E_DE();
void test_FX29_DE();
void test_FX33_DE();
void test_FX55_DE();
void test_FX65_DE();
void test_decodeAndExecuteInstructions();
void RUN_ALL_CHIP8_TESTS();


#endif