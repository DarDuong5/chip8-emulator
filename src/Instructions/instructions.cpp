#include "instructions.hpp"
#include "../Chip8/chip8.hpp"

void opcode_00E0(Chip8* chip8) {
    for (int h = 0; h < DISPLAY_HEIGHT; h++) {
        for (int w = 0; w < DISPLAY_WIDTH; w++) {
            chip8->display[h][w] = 0;
        }
    }
    chip8->PC += 2;
}