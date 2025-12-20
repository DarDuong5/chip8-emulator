#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include <iostream>
#include "../Chip8/chip8.hpp"

void opcode_00E0(Chip8* chip8);
void opcode_00EE(Chip8* chip8);
void opcode_1NNN(Chip8* chip8);
void opcode_2NNN(Chip8* chip8);
void opcode_3XKK(Chip8* chip8);
void opcode_4XKK(Chip8* chip8);
void opcode_5XY0(Chip8* chip8);
void opcode_6XKK(Chip8* chip8);
void opcode_7XKK(Chip8* chip8);
void opcode_8XY0(Chip8* chip8);
void opcode_8XY1(Chip8* chip8);
void opcode_8XY2(Chip8* chip8);
void opcode_8XY3(Chip8* chip8);
void opcode_8XY4(Chip8* chip8);
void opcode_8XY5(Chip8* chip8);
void opcode_8XY6(Chip8* chip8);
void opcode_8XY7(Chip8* chip8);
void opcode_8XYE(Chip8* chip8);
void opcode_9XY0(Chip8* chip8);
void opcode_ANNN(Chip8* chip8);
void opcode_BNNN(Chip8* chip8);
void opcode_CXKK(Chip8* chip8);
void opcode_DXYN(Chip8* chip8);
void opcode_EX9E(Chip8* chip8);
void opcode_EXA1(Chip8* chip8);
void opcode_FX07(Chip8* chip8);
void opcode_FX0A(Chip8* chip8);
void opcode_FX15(Chip8* chip8);
void opcode_FX18(Chip8* chip8);
void opcode_FX1E(Chip8* chip8);
void opcode_FX29(Chip8* chip8);
void opcode_FX33(Chip8* chip8);
void opcode_FX55(Chip8* chip8);
void opcode_FX65(Chip8* chip8);


#endif
