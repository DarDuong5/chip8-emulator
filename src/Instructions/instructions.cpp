#include "instructions.hpp"
#include "../Chip8/chip8.hpp"


// TODO: Error if values are NULL.

// 00E0: CLS
// Clears the display screen.
void opcode_00E0(Chip8* chip8) {
    for (int h = 0; h < DISPLAY_HEIGHT; h++) {
        for (int w = 0; w < DISPLAY_WIDTH; w++) {
            chip8->display[w][h] = 0;
        }
    }
    chip8->PC += 2;
}

// 00EE: RET
// Return from a subroutine.
void opcode_00EE(Chip8* chip8) {
    chip8->stackPointer -= 1;
    chip8->PC = chip8->stack[chip8->stackPointer];
}

// 1NNN: JP addr
// Jump to location NNN. The interpreter sets the program counter to NNN.
void opcode_1NNN(Chip8* chip8) {
    uint16_t nnn = chip8->opcode & 0x0FFF;
    chip8->PC = nnn;
}

// 2NNN: CALL addr
// Call subroutine at NNN.
void opcode_2NNN(Chip8* chip8) {
    uint16_t nnn = chip8->opcode & 0x0FFF;
    chip8->stack[chip8->stackPointer] = chip8->PC;
    chip8->stackPointer += 1;
    chip8->PC = nnn;
}

// 3XKK: SE Vx, byte
// Skip next instruction if Vx = kk.
void opcode_3XKK(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t kk = chip8->opcode & 0x00FF;

    if (chip8->varRegisters[x] == kk) {
        chip8->PC += 4;
    } else {
        chip8->PC += 2;
    }
}

// 4XKK: SNE Vx, byte
// Skip next instruction if Vx != kk.
void opcode_4XKK(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t kk = chip8->opcode & 0x00FF; 

    if (chip8->varRegisters[x] != kk) {
        chip8->PC += 4;
    } else {
        chip8->PC += 2;
    }
}

// 5XY0: SE Vx, Vy
// Skip next instruction if Vx = Vy.
void opcode_5XY0(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;

    if (chip8->varRegisters[x] == chip8->varRegisters[y]) {
        chip8->PC += 4;
    } else {
        chip8->PC += 2;
    }
}

// 6XKK: LD Vx, byte
// Set Vx = kk.
void opcode_6XKK(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t kk = chip8->opcode & 0x00FF;
    chip8->varRegisters[x] = kk;
    chip8->PC += 2;
}

// 7XKK: ADD Vx, byte
// Set Vx = Vx + kk.
void opcode_7XKK(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t kk = chip8->opcode & 0x00FF;
    chip8->varRegisters[x] += kk;
    chip8->PC += 2;
}

// 8XY0: LD Vx, Vy
// Set Vx = Vy.
void opcode_8XY0(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    chip8->varRegisters[x] = chip8->varRegisters[y];
    chip8->PC += 2;
}

// 8XY1: OR Vx, Vy
// Set Vx = Vx OR Vy.
void opcode_8XY1(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    chip8->varRegisters[x] |= chip8->varRegisters[y];
    chip8->PC += 2;
}

// 8XY2: AND Vx, Vy
// Set Vx = Vx AND Vy.
void opcode_8XY2(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    chip8->varRegisters[x] &= chip8->varRegisters[y];
    chip8->PC += 2;
}

// 8XY3: XOR Vx, Vy
// Set Vx = Vx XOR Vy.
void opcode_8XY3(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    chip8->varRegisters[x] ^= chip8->varRegisters[y];
    chip8->PC += 2;
}

// 8XY4: ADD Vx, Vy
// Set Vx = Vx + Vy, set VF = carry if (Vx + Vy) is greater than 255.
void opcode_8XY4(Chip8* chip8);

