#include "chip8.hpp"
#include "../Instructions/instructions.hpp"

void updateTimers(Chip8* chip8) {
    if (chip8->delayTimer > 0) {
        chip8->delayTimer--;
    }

    if (chip8->soundTimer > 0) {
        chip8->soundTimer--;
    }
}

void fetchInstructions(Chip8* chip8) {
    chip8->opcode = (chip8->memory[chip8->PC] << 8) | chip8->memory[chip8->PC + 1];
}

void decodeAndExecuteInstructions(Chip8* chip8) {
    fetchInstructions(chip8);

    switch(chip8->opcode & 0xF000) {
        case 0x0000:
            switch (chip8->opcode & 0xFFFF) {
                case 0x00E0:
                    opcode_00E0(chip8);
                    break;
                case 0x00EE:
                    opcode_00EE(chip8);
                    break;
                default:
                    std::cout << "No valid opcode for 0x0000." << std::endl;
            }
            break;
        case 0x1000:
            opcode_1NNN(chip8);
            break;
        case 0x2000:
            opcode_2NNN(chip8);
            break;
        case 0x3000:
            opcode_3XKK(chip8);
            break;
        case 0x4000:
            opcode_4XKK(chip8);
            break;
        case 0x5000:
            opcode_5XY0(chip8);
            break;
        case 0x6000:
            opcode_6XKK(chip8);
            break;
        case 0x7000:
            opcode_7XKK(chip8);
            break;
        case 0x8000:
            switch (chip8->opcode & 0xF00F) {
                case 0x8000:
                    opcode_8XY0(chip8);
                    break;
                case 0x8001:
                    opcode_8XY1(chip8);
                    break;
                case 0x8002:
                    opcode_8XY2(chip8);
                    break;
                case 0x8003:
                    opcode_8XY3(chip8);
                    break;
                case 0x8004:
                    opcode_8XY4(chip8);
                    break;
                case 0x8005:
                    opcode_8XY5(chip8);
                    break;
                case 0x8006:
                    opcode_8XY6(chip8);
                    break;
                case 0x8007:
                    opcode_8XY7(chip8);
                    break;
                case 0x800E:
                    opcode_8XYE(chip8);
                    break;
                default:
                    std::cout << "No valid opcode for 0x8000." << std::endl;
            }
            break;
        case 0x9000:
            opcode_9XY0(chip8);
            break;
        case 0xA000:
            opcode_ANNN(chip8);
            break;
        case 0xB000:
            opcode_BNNN(chip8);
            break;
        case 0xC000:
            opcode_CXKK(chip8);
            break;
        case 0xD000:
            opcode_DXYN(chip8);
            break;
        case 0xE000:
            switch(chip8->opcode & 0xF0FF) {
                case 0xE0A1:
                    opcode_EXA1(chip8);
                    break;
                case 0xE09E:
                    opcode_EX9E(chip8);
                    break;
                default:
                    std::cout << "No valid opcode for 0xE000." << std::endl;
            }
            break;
        case 0xF000:
            switch(chip8->opcode & 0xF0FF) {
                case 0xF007:
                    opcode_FX07(chip8);
                    break;
                case 0xF00A:
                    opcode_FX0A(chip8);
                    break;
                case 0xF015:
                    opcode_FX15(chip8);
                    break;
                case 0xF018:
                    opcode_FX18(chip8);
                    break;
                case 0xF01E:
                    opcode_FX1E(chip8);
                    break;
                case 0xF029:
                    opcode_FX29(chip8);
                    break;
                case 0xF033:
                    opcode_FX33(chip8);
                    break;
                case 0xF055:
                    opcode_FX55(chip8);
                    break;
                case 0xF065:
                    opcode_FX65(chip8);
                    break;
                default:
                    std::cout << "No valid opcode for 0xF000." << std::endl;
            }
            break;
        default:
            std::cout << "No valid opcode." << std::endl;
    }
}

