#include "test_instructions.hpp"
#include "../Chip8/chip8.hpp"
#include "../Instructions/instructions.hpp"

// Test for opcode 00E0: CLS
void test_00E0() {
    Chip8 chip8{};

    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
        for (int x = 0; x < DISPLAY_WIDTH; x++) {
            chip8.display[x][y] = 1;
        }
    }

    opcode_00E0(&chip8);

    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
        for (int x = 0; x < DISPLAY_WIDTH; x++) {
            assert(chip8.display[x][y] == 0);
        }
    }

    std::cout << "Test for opcode 00E0 passed!\n";
}

// Test for opcode 00EE: RET
void test_00EE() {
    Chip8 chip8{};
    chip8.stack[0] = 100;
    chip8.stack[1] = 200;
    chip8.stack[2] = 300;
    chip8.stackPointer = 3;

    opcode_00EE(&chip8);

    assert(chip8.stackPointer == 2);
    assert(chip8.PC == 300);

    std::cout << "Test for opcode 00EE passed!\n";
}

// Test for opcode 1NNN: JP addr
void test_1NNN() {
    Chip8 chip8{};
    chip8.opcode = 0x1234;

    opcode_1NNN(&chip8);

    assert(chip8.PC == 0x234);

    std::cout << "Test for opcode 1NNN passed!\n";
}

// Test for opcode 2NNN: CALL addr
void test_2NNN() {
    Chip8 chip8{};
    chip8.opcode = 0x2456;
    chip8.PC = 100;
    chip8.stackPointer = 0;

    opcode_2NNN(&chip8);

    assert(chip8.stack[0] == 100);
    assert(chip8.stackPointer == 1);
    assert(chip8.PC == 0x456);

    std::cout << "Test for opcode 2NNN passed!\n";
}

// Test for opcode 3XKK: SE Vx, byte
void test_3XKK() {
    Chip8 chip8{};
    chip8.opcode = 0x3123;
    chip8.varRegisters[1] = 0x23;
    chip8.PC = 100;

    opcode_3XKK(&chip8);

    assert(chip8.PC == 104);

    std::cout << "Test for opcode 3XKK passed!\n";
}

// Test for opcode 4XKK: SNE Vx, byte
void test_4XKK() {
    Chip8 chip8{};
    chip8.opcode = 0x4123;
    chip8.varRegisters[1] = 0x22;
    chip8.PC = 100;

    opcode_4XKK(&chip8);

    assert(chip8.PC == 104);

    std::cout << "Test for opcode 4XKK passed!\n";
}

// Test for opcode 5XY0: SE Vx, Vy
void test_5XY0() {
    Chip8 chip8{};
    chip8.opcode = 0x5120;
    chip8.varRegisters[1] = 5;
    chip8.varRegisters[2] = 5;
    chip8.PC = 100;

    opcode_5XY0(&chip8);

    assert(chip8.PC == 104);

    std::cout << "Test for opcode 5XY0 passed!\n";
}

// Test for opcode 6XKK: LD Vx, byte
void test_6XKK() {
    Chip8 chip8{};
    chip8.opcode = 0x61FF;

    opcode_6XKK(&chip8);

    assert(chip8.varRegisters[1] == 0xFF);

    std::cout << "Test for opcode 6XKK passed!\n";
}

// Test for opcode 7XKK: ADD Vx, byte
void test_7XKK() {
    Chip8 chip8{};
    chip8.opcode = 0x7101;
    chip8.varRegisters[1] = 5;

    opcode_7XKK(&chip8);

    assert(chip8.varRegisters[1] == 6);

    std::cout << "Test for opcode 7XKK passed!\n";
}

// Test for opcode 8XY4: ADD Vx, Vy
void test_8XY4() {
    Chip8 chip8{};
    chip8.opcode = 0x8124;
    chip8.varRegisters[1] = 200;
    chip8.varRegisters[2] = 100;

    opcode_8XY4(&chip8);

    assert(chip8.varRegisters[1] == 44);
    assert(chip8.varRegisters[0xF] == 1);

    std::cout << "Test for opcode 8XY4 passed!\n";
}

// Test for opcode 8XY6: SHR Vx
void test_8XY6() {
    Chip8 chip8{};
    chip8.opcode = 0x8106;
    chip8.varRegisters[1] = 3;

    opcode_8XY6(&chip8);

    assert(chip8.varRegisters[1] == 1);
    assert(chip8.varRegisters[0xF] == 1);

    std::cout << "Test for opcode 8XY6 passed!\n";
}

// Test for opcode 8XYE: SHL Vx
void test_8XYE() {
    Chip8 chip8{};
    chip8.opcode = 0x810E;
    chip8.varRegisters[1] = 0x80;

    opcode_8XYE(&chip8);

    assert(chip8.varRegisters[1] == 0);
    assert(chip8.varRegisters[0xF] == 1);

    std::cout << "Test for opcode 8XYE passed!\n";
}

// Test for opcode ANNN: LD I, addr
void test_ANNN() {
    Chip8 chip8{};
    chip8.opcode = 0xA123;

    opcode_ANNN(&chip8);

    assert(chip8.I == 0x123);

    std::cout << "Test for opcode ANNN passed!\n";
}

// Test for opcode CXKK: RND Vx, byte
void test_CXKK() {
    Chip8 chip8{};
    chip8.opcode = 0xC1FF;

    opcode_CXKK(&chip8);

    assert((chip8.varRegisters[1] & 0xFF) == chip8.varRegisters[1]);

    std::cout << "Test for opcode CXKK passed!\n";
}

// Test for opcode DXYN: DRW Vx, Vy, nibble
void test_DXYN() {
    Chip8 chip8{};
    chip8.opcode = 0xD011;
    chip8.I = 0x300;
    chip8.memory[0x300] = 0xFF;
    chip8.varRegisters[0] = 0;
    chip8.varRegisters[1] = 0;

    opcode_DXYN(&chip8);

    for (int i = 0; i < 8; i++) {
        assert(chip8.display[i][0] == 0xFFFFFFFF);
    }

    std::cout << "Test for opcode DXYN passed!\n";
}

// Test for opcode FX33: LD B, Vx
void test_FX33() {
    Chip8 chip8{};
    chip8.opcode = 0xF133;
    chip8.I = 300;
    chip8.varRegisters[1] = 123;

    opcode_FX33(&chip8);

    assert(chip8.memory[300] == 1);
    assert(chip8.memory[301] == 2);
    assert(chip8.memory[302] == 3);

    std::cout << "Test for opcode FX33 passed!\n";
}

// Test for opcode 8XY0: LD Vx, Vy
void test_8XY0() {
    Chip8 chip8{};
    chip8.opcode = 0x8120; // V1 = V2
    chip8.varRegisters[2] = 42;

    opcode_8XY0(&chip8);

    assert(chip8.varRegisters[1] == 42);
    std::cout << "Test for opcode 8XY0 passed!" << std::endl;
}

// Test for opcode 8XY1: OR Vx, Vy
void test_8XY1() {
    Chip8 chip8{};
    chip8.opcode = 0x8121;
    chip8.varRegisters[1] = 0x0F;
    chip8.varRegisters[2] = 0xF0;

    opcode_8XY1(&chip8);

    assert(chip8.varRegisters[1] == 0xFF);
    std::cout << "Test for opcode 8XY1 passed!" << std::endl;
}

// Test for opcode 8XY2: AND Vx, Vy
void test_8XY2() {
    Chip8 chip8{};
    chip8.opcode = 0x8122;
    chip8.varRegisters[1] = 0xF0;
    chip8.varRegisters[2] = 0x0F;

    opcode_8XY2(&chip8);

    assert(chip8.varRegisters[1] == 0x00);
    std::cout << "Test for opcode 8XY2 passed!" << std::endl;
}

// Test for opcode 8XY3: XOR Vx, Vy
void test_8XY3() {
    Chip8 chip8{};
    chip8.opcode = 0x8123;
    chip8.varRegisters[1] = 0xAA;
    chip8.varRegisters[2] = 0xFF;

    opcode_8XY3(&chip8);

    assert(chip8.varRegisters[1] == 0x55);
    std::cout << "Test for opcode 8XY3 passed!" << std::endl;
}

// Test for opcode 8XY5: SUB Vx, Vy
void test_8XY5() {
    Chip8 chip8{};
    chip8.opcode = 0x8125;
    chip8.varRegisters[1] = 10;
    chip8.varRegisters[2] = 5;

    opcode_8XY5(&chip8);

    assert(chip8.varRegisters[1] == 5);
    assert(chip8.varRegisters[0xF] == 1);
    std::cout << "Test for opcode 8XY5 passed!" << std::endl;
}

// Test for opcode 8XY7: SUBN Vx, Vy
void test_8XY7() {
    Chip8 chip8{};
    chip8.opcode = 0x8127;
    chip8.varRegisters[1] = 5;
    chip8.varRegisters[2] = 10;

    opcode_8XY7(&chip8);

    assert(chip8.varRegisters[1] == 5);
    assert(chip8.varRegisters[0xF] == 1);
    std::cout << "Test for opcode 8XY7 passed!" << std::endl;
}

// Test for opcode 9XY0: SNE Vx, Vy
void test_9XY0() {
    Chip8 chip8{};
    chip8.opcode = 0x9120;
    chip8.varRegisters[1] = 1;
    chip8.varRegisters[2] = 2;
    chip8.PC = 100;

    opcode_9XY0(&chip8);

    assert(chip8.PC == 104);
    std::cout << "Test for opcode 9XY0 passed!" << std::endl;
}

// Test for opcode BNNN: JP V0, addr
void test_BNNN() {
    Chip8 chip8{};
    chip8.opcode = 0xB300;
    chip8.varRegisters[0] = 5;

    opcode_BNNN(&chip8);

    assert(chip8.PC == 0x305);
    std::cout << "Test for opcode BNNN passed!" << std::endl;
}

// Test for opcode EX9E: SKP Vx
void test_EX9E() {
    Chip8 chip8{};
    chip8.opcode = 0xE19E;
    chip8.varRegisters[1] = 3;
    chip8.keyPad[3] = 1;
    chip8.PC = 200;

    opcode_EX9E(&chip8);

    assert(chip8.PC == 204);
    std::cout << "Test for opcode EX9E passed!" << std::endl;
}

// Test for opcode EXA1: SKNP Vx
void test_EXA1() {
    Chip8 chip8{};
    chip8.opcode = 0xE1A1;
    chip8.varRegisters[1] = 4;
    chip8.keyPad[4] = 0;
    chip8.PC = 300;

    opcode_EXA1(&chip8);

    assert(chip8.PC == 304);
    std::cout << "Test for opcode EXA1 passed!" << std::endl;
}

// Test for opcode FX07: LD Vx, DT
void test_FX07() {
    Chip8 chip8{};
    chip8.opcode = 0xF107;
    chip8.delayTimer = 99;

    opcode_FX07(&chip8);

    assert(chip8.varRegisters[1] == 99);
    std::cout << "Test for opcode FX07 passed!" << std::endl;
}

// Test for opcode FX0A: LD Vx, K
void test_FX0A() {
    Chip8 chip8{};
    chip8.opcode = 0xF10A;
    chip8.keyPad[7] = 1;

    opcode_FX0A(&chip8);

    assert(chip8.varRegisters[1] == 7);
    std::cout << "Test for opcode FX0A passed!" << std::endl;
}

// Test for opcode FX15: LD DT, Vx
void test_FX15() {
    Chip8 chip8{};
    chip8.opcode = 0xF115;
    chip8.varRegisters[1] = 55;

    opcode_FX15(&chip8);

    assert(chip8.delayTimer == 55);
    std::cout << "Test for opcode FX15 passed!" << std::endl;
}

// Test for opcode FX18: LD ST, Vx
void test_FX18() {
    Chip8 chip8{};
    chip8.opcode = 0xF118;
    chip8.varRegisters[1] = 33;

    opcode_FX18(&chip8);

    assert(chip8.soundTimer == 33);
    std::cout << "Test for opcode FX18 passed!" << std::endl;
}

// Test for opcode FX1E: ADD I, Vx
void test_FX1E() {
    Chip8 chip8{};
    chip8.opcode = 0xF11E;
    chip8.I = 100;
    chip8.varRegisters[1] = 20;

    opcode_FX1E(&chip8);

    assert(chip8.I == 120);
    std::cout << "Test for opcode FX1E passed!" << std::endl;
}

// Test for opcode FX29: LD F, Vx
void test_FX29() {
    Chip8 chip8{};
    chip8.opcode = 0xF129;
    chip8.varRegisters[1] = 3;

    opcode_FX29(&chip8);

    assert(chip8.I == FONTSET_START_ADDRESS + 15);
    std::cout << "Test for opcode FX29 passed!" << std::endl;
}

// Test for opcode FX55: LD [I], Vx
void test_FX55() {
    Chip8 chip8{};
    chip8.opcode = 0xF355;
    chip8.I = 300;
    chip8.varRegisters[0] = 1;
    chip8.varRegisters[1] = 2;
    chip8.varRegisters[2] = 3;
    chip8.varRegisters[3] = 4;

    opcode_FX55(&chip8);

    assert(chip8.memory[300] == 1);
    assert(chip8.memory[301] == 2);
    assert(chip8.memory[302] == 3);
    assert(chip8.memory[303] == 4);
    std::cout << "Test for opcode FX55 passed!" << std::endl;
}

// Test for opcode FX65: LD Vx, [I]
void test_FX65() {
    Chip8 chip8{};
    chip8.opcode = 0xF365;
    chip8.I = 400;
    chip8.memory[400] = 9;
    chip8.memory[401] = 8;
    chip8.memory[402] = 7;
    chip8.memory[403] = 6;

    opcode_FX65(&chip8);

    assert(chip8.varRegisters[0] == 9);
    assert(chip8.varRegisters[1] == 8);
    assert(chip8.varRegisters[2] == 7);
    assert(chip8.varRegisters[3] == 6);
    std::cout << "Test for opcode FX65 passed!" << std::endl;
}


/*


g++ -Wall -Wextra -g3 \
    src/Chip8/chip8.cpp \
    src/Display/display.cpp \
    src/Instructions/instructions.cpp \
    src/Keypad/keypad.cpp \
    src/Tests/test_instructions.cpp \
    -o output/test_instructions
*/