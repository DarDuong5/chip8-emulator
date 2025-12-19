#include "instructions.hpp"
#include "../Chip8/chip8.hpp"
#include "../Display/display.hpp"


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
void opcode_8XY4(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    uint16_t sum = chip8->varRegisters[x] + chip8->varRegisters[y];
    if (sum > 255) {
        chip8->varRegisters[0xF] = 1;
    } else {
        chip8->varRegisters[0xF] = 0;
    }
    chip8->varRegisters[x] = sum & 0x00FF;
    chip8->PC += 2;
}

// 8XY5: SUB Vx, Vy
// Set Vx = Vx - Vy, set VF = NOT borrow if Vx > Vy.
void opcode_8XY5(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    if (chip8->varRegisters[x] > chip8->varRegisters[y]) {
        chip8->varRegisters[0xF] = 1;
    } else {
        chip8->varRegisters[0xF] = 0;
    }
    chip8->varRegisters[x] -= chip8->varRegisters[y];
    chip8->PC += 2;
}

// 8XY6: SHR Vx
// Set Vx = Vx SHR 1, set VF to 1 if the least-significant bit of Vx is 1.
void opcode_8XY6(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    chip8->varRegisters[0xF] = chip8->varRegisters[x] & 0x0001;
    chip8->varRegisters[x] >>= 1;
    chip8->PC += 2;
}

// 8XY7: SUBN Vx, Vy
// Set Vx = Vy - Vx, set VF = NOT borrow if Vy > Vx.
void opcode_8XY7(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    if (chip8->varRegisters[y] > chip8->varRegisters[x]) {
        chip8->varRegisters[0xF] = 1;
    } else {
        chip8->varRegisters[0xF] = 0;
    }
    chip8->varRegisters[x] = chip8->varRegisters[y] - chip8->varRegisters[x];
    chip8->PC += 2;
}

// 8XYE: SHL Vx {, Vy}
// Set Vx = Vx SHL 1, set VF to 1 if the most-significant bit of Vx is 1.
void opcode_8XYE(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    chip8->varRegisters[0xF] = (chip8->varRegisters[x] & 0x80) >> 7;
    chip8->varRegisters[x] <<= 1;
    chip8->PC += 2;
}

// 9XY0: SNE Vx, Vy
// Skip next instruction if Vx != Vy.
void opcode_9XY0(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    if (chip8->varRegisters[x] != chip8->varRegisters[y]) {
        chip8->PC += 4;
    } else {
        chip8->PC += 2;
    }
}

// ANNN: LD I, addr
// Set I = NNN.
void opcode_ANNN(Chip8* chip8) {
    uint16_t nnn = chip8->opcode & 0x0FFF;
    chip8->I = nnn;
    chip8->PC += 2;
}

// BNNN: JP V0, addr
// Jump to location nnn + V0.
void opcode_BNNN(Chip8* chip8) {
    uint16_t nnn = chip8->opcode & 0x0FFF;
    chip8->PC = nnn + chip8->varRegisters[0];
}

// CXKK: RND Vx, byte
// Set Vx = random byte AND kk.
void opcode_CXKK(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t kk = chip8->opcode & 0x00FF;
    chip8->varRegisters[x] = (rand() % 256) & kk;
    chip8->PC += 2;
}

// DXYN: DRW Vx, Vy, nibble
// Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
void opcode_DXYN(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    uint8_t height = opcode & 0x000F;

    uint8_t xPos = registers[x] % DISPLAY_WIDTH;
    uint8_t yPos = registers[y] % DISPLAY_HEIGHT;

    chip8->varRegisters[0xF] = 0;

    for (int row = 0; row < height; row++) {
        uint8_t spriteByte = chip8->memory[chip8->I + row];
        for (int col = 0; col < 8; col++) {
            if (spriteByte & (0x80 >> col) != 0) {
                uint8_t drawX = (xPos + col) % DISPLAY_WIDTH;
                uint8_t drawY = (yPos + row) % DISPLAY_HEIGHT;

                if (chip8->display[drawX][drawY] != 0) {
                    chip8->varRegisters[0xF] = 1;
                }

                chip8->display[drawX][drawY] ^= ON;
            }

        }

    }
    chip8->PC += 2
}