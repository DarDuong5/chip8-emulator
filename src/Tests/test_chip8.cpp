#include "test_chip8.hpp"
#include "../Chip8/chip8.hpp"
#include "../Instructions/instructions.hpp"

void test_updateTimers() {
    Chip8 chip8{};

    chip8.soundTimer = 10;
    chip8.delayTimer = 15;

    while (chip8.soundTimer != 0 || chip8.delayTimer != 0) {
        updateTimers(&chip8);
    }

    assert(chip8.soundTimer == 0);
    assert(chip8.delayTimer == 0);

    std::cout << "Tests for updating timers passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode 00E0: CLS
void test_00E0_DE() {
    Chip8 chip8{};
    chip8.display[0][0] = 1;

    LOAD_OPCODE(chip8, 0x00E0);
    decodeAndExecuteInstructions(&chip8);

    assert(chip8.display[0][0] == 0);
    std::cout << "Fetch, decode, and execution tests for 00E0 passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode 00EE: RET
void test_00EE_DE() {
    Chip8 chip8{};
    chip8.stackPointer = 1;
    chip8.stack[0] = 0x300;

    LOAD_OPCODE(chip8, 0x00EE);
    decodeAndExecuteInstructions(&chip8);

    assert(chip8.PC == 0x300);
    assert(chip8.stackPointer == 0);
    std::cout << "Fetch, decode, and execution tests for 00EE passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode 1NNN: JP addr
void test_1NNN_DE() {
    Chip8 chip8{};
    LOAD_OPCODE(chip8, 0x1234);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.PC == 0x234);
    std::cout << "Fetch, decode, and execution tests for 1NNN passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode 2NNN: CALL addr
void test_2NNN_DE() {
    Chip8 chip8{};
    LOAD_OPCODE(chip8, 0x2456);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.stack[0] == 0x200);
    assert(chip8.stackPointer == 1);
    assert(chip8.PC == 0x456);
    std::cout << "Fetch, decode, and execution tests for 2NNN passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode 3XKK: SE Vx, byte
void test_3XKK_DE() {
    Chip8 chip8{};
    chip8.varRegisters[1] = 0x42;
    LOAD_OPCODE(chip8, 0x3142);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.PC == 0x204);
    std::cout << "Fetch, decode, and execution tests for 3XKK passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode 4XKK: SNE Vx, byte
void test_4XKK_DE() {
    Chip8 chip8{};
    chip8.varRegisters[2] = 0x10;
    LOAD_OPCODE(chip8, 0x4211);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.PC == 0x204);
    std::cout << "Fetch, decode, and execution tests for 4XKK passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode 5XY0: SE Vx, Vy
void test_5XY0_DE() {
    Chip8 chip8{};
    chip8.varRegisters[1] = 5;
    chip8.varRegisters[2] = 5;
    LOAD_OPCODE(chip8, 0x5120);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.PC == 0x204);
    std::cout << "Fetch, decode, and execution tests for 5XY0 passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode 6XKK: LD Vx, byte
void test_6XKK_DE() {
    Chip8 chip8{};
    LOAD_OPCODE(chip8, 0x60FF);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.varRegisters[0] == 0xFF);
    std::cout << "Fetch, decode, and execution tests for 6XKK passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode 7XKK: ADD Vx, byte
void test_7XKK_DE() {
    Chip8 chip8{};
    chip8.varRegisters[0] = 1;
    LOAD_OPCODE(chip8, 0x7001);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.varRegisters[0] == 2);
    std::cout << "Fetch, decode, and execution tests for 7XKK passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode 8XY0: LD Vx, Vy
void test_8XY0_DE() { 
    Chip8 chip8{};
    chip8.varRegisters[1] = 0x42;
    chip8.varRegisters[2] = 0x10;
    LOAD_OPCODE(chip8, 0x8120);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.varRegisters[1] == 0x10);
    std::cout << "Fetch, decode, and execution tests for 8XY0 passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode 8XY1: OR Vx, Vy
void test_8XY1_DE() { 
    Chip8 chip8{};
    chip8.varRegisters[1] = 0xF0;
    chip8.varRegisters[2] = 0x0F;
    LOAD_OPCODE(chip8, 0x8121);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.varRegisters[1] == 0xFF);
    std::cout << "Fetch, decode, and execution tests for 8XY1 passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode 8XY2: AND Vx, Vy
void test_8XY2_DE() {
    Chip8 chip8{};
    chip8.varRegisters[1] = 0xF0;
    chip8.varRegisters[2] = 0x0F;
    LOAD_OPCODE(chip8, 0x8122);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.varRegisters[1] == 0x00);
    std::cout << "Fetch, decode, and execution tests for 8XY2 passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode 8XY3: XOR Vx, Vy
void test_8XY3_DE() {
    Chip8 chip8{};
    chip8.varRegisters[1] = 0xAA;
    chip8.varRegisters[2] = 0xFF;
    LOAD_OPCODE(chip8, 0x8123);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.varRegisters[1] == 0x55);
    std::cout << "Fetch, decode, and execution tests for 8XY3 passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode 8XY4: ADD Vx, Vy
void test_8XY4_DE() {
    Chip8 chip8{};
    chip8.varRegisters[1] = 200;
    chip8.varRegisters[2] = 100;
    LOAD_OPCODE(chip8, 0x8124);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.varRegisters[1] == 44);
    assert(chip8.varRegisters[0xF] == 1);
    std::cout << "Fetch, decode, and execution tests for 8XY4 passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode 8XY5: SUB Vx, Vy
void test_8XY5_DE() {
    Chip8 chip8{};
    chip8.varRegisters[1] = 10;
    chip8.varRegisters[2] = 3;
    LOAD_OPCODE(chip8, 0x8125);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.varRegisters[1] == 7);
    assert(chip8.varRegisters[0xF] == 1);
    std::cout << "Fetch, decode, and execution tests for 8XY5 passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode 8XY6: SHR Vx
void test_8XY6_DE() {
    Chip8 chip8{};
    chip8.varRegisters[1] = 0x03;
    LOAD_OPCODE(chip8, 0x8126);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.varRegisters[1] == 0x01);
    assert(chip8.varRegisters[0xF] == 1);
    std::cout << "Fetch, decode, and execution tests for 8XY6 passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode 8XY7: SUBN Vx, Vy
void test_8XY7_DE() {
    Chip8 chip8{};
    chip8.varRegisters[1] = 3;
    chip8.varRegisters[2] = 10;
    LOAD_OPCODE(chip8, 0x8127);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.varRegisters[1] == 7);
    assert(chip8.varRegisters[0xF] == 1);
    std::cout << "Fetch, decode, and execution tests for 8XY7 passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode 8XY0: SHL Vx
void test_8XYE_DE() {
    Chip8 chip8{};
    chip8.varRegisters[1] = 0x80;
    LOAD_OPCODE(chip8, 0x812E);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.varRegisters[1] == 0x00);
    assert(chip8.varRegisters[0xF] == 1);
    std::cout << "Fetch, decode, and execution tests for 8XYE passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode 9XY0: SNE Vx, Vy
void test_9XY0_DE() {
    Chip8 chip8{};
    chip8.varRegisters[1] = 1;
    chip8.varRegisters[2] = 2;
    LOAD_OPCODE(chip8, 0x9120);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.PC == 0x204);
    std::cout << "Fetch, decode, and execution tests for 9XY0 passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode ANNN: LD I, addr
void test_ANNN_DE() {
    Chip8 chip8{};
    LOAD_OPCODE(chip8, 0xA123);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.I == 0x123);
    std::cout << "Fetch, decode, and execution tests for ANNN passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode BNNN: JP V0, addr
void test_BNNN_DE() {
    Chip8 chip8{};
    chip8.varRegisters[0] = 5;
    LOAD_OPCODE(chip8, 0xB100);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.PC == 0x105);
    std::cout << "Fetch, decode, and execution tests for BNNN passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode CXKK: RND Vx, byte
void test_CXKK_DE() {
    Chip8 chip8{};
    LOAD_OPCODE(chip8, 0xC00F);

    decodeAndExecuteInstructions(&chip8);

    assert((chip8.varRegisters[0] & 0xF0) == 0);
    std::cout << "Fetch, decode, and execution tests for CXKK passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode DXYN: DRW Vx, Vy, nibble
void test_DXYN_DE() {
    Chip8 chip8{};
    chip8.I = 0x300;
    chip8.memory[0x300] = 0xFF;
    chip8.varRegisters[0] = 0;
    chip8.varRegisters[1] = 0;

    LOAD_OPCODE(chip8, 0xD011);
    decodeAndExecuteInstructions(&chip8); // no collision

    chip8.PC = 0x200; 
    decodeAndExecuteInstructions(&chip8); // collision

    assert(chip8.varRegisters[0xF] == 1);
    std::cout << "Fetch, decode, and execution tests for DXYN passed!" << std::endl;
}


// Fetch, decode, and execute tests for opcode EXA1: SNKP Vx
void test_EXA1_DE() {
    Chip8 chip8{};
    chip8.keyPad[0] = 0;
    LOAD_OPCODE(chip8, 0xE1A1);
    
    decodeAndExecuteInstructions(&chip8); // not pressed

    assert(chip8.PC == 0x204);

    chip8.keyPad[0] = 1;
    LOAD_OPCODE(chip8, 0xE2A1);
    
    decodeAndExecuteInstructions(&chip8); // pressed

    assert(chip8.PC == 0x202);
    std::cout << "Fetch, decode, and execution tests for EXA1 passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode EX9E: SKP Vx
void test_EX9E_DE() {
    Chip8 chip8{};
    chip8.keyPad[5] = 1;
    chip8.varRegisters[1] = 5;

    LOAD_OPCODE(chip8, 0xE19E);
    decodeAndExecuteInstructions(&chip8);

    assert(chip8.PC == 0x204);
    std::cout << "Fetch, decode, and execution tests for EX9E passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode FX07: LD Vx, DT
void test_FX07_DE() {
    Chip8 chip8{};
    chip8.delayTimer = 42;
    LOAD_OPCODE(chip8, 0xF107);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.varRegisters[1] == 42);
    std::cout << "Fetch, decode, and execution tests for FX07 passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode FX0A: LD Vx, K
void test_FX0A_DE() {
    Chip8 chip8{};
    chip8.keyPad[9] = 1;
    chip8.varRegisters[0] = 0xF;
    LOAD_OPCODE(chip8, 0xF00A);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.varRegisters[0] == 9);
    std::cout << "Fetch, decode, and execution tests for FX0A passed!" << std::endl;
}


// Fetch, decode, and execute tests for opcode FX15: LD DT, Vx
void test_FX15_DE() {
    Chip8 chip8{};
    chip8.varRegisters[1] = 123;
    LOAD_OPCODE(chip8, 0xF115);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.delayTimer == 123);
    std::cout << "Fetch, decode, and execution tests for FX15 passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode FX18: LD ST, Vx
void test_FX18_DE() {
    Chip8 chip8{};
    chip8.varRegisters[1] = 99;
    LOAD_OPCODE(chip8, 0xF118);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.soundTimer == 99);
    std::cout << "Fetch, decode, and execution tests for FX18 passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode FX1E: ADD I, Vx
void test_FX1E_DE() {
    Chip8 chip8{};
    chip8.I = 0x200;
    chip8.varRegisters[1] = 0x30;
    LOAD_OPCODE(chip8, 0xF11E);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.I == 0x230);
    std::cout << "Fetch, decode, and execution tests for FX1E passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode FX29: LD F, Vx
void test_FX29_DE() { 
    Chip8 chip8{};
    chip8.varRegisters[1] = 5; // font for '5'
    LOAD_OPCODE(chip8, 0xF129);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.I == 0x050 + 5 * 5); // each sprite 5 bytes
    std::cout << "Fetch, decode, and execution tests for FX29 passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode FX33: LD B, Vx
void test_FX33_DE() {
    Chip8 chip8{};
    chip8.I = 0x300;
    chip8.varRegisters[0] = 123;
    LOAD_OPCODE(chip8, 0xF033);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.memory[0x300] == 1);
    assert(chip8.memory[0x301] == 2);
    assert(chip8.memory[0x302] == 3);
    std::cout << "Fetch, decode, and execution tests for FX33 passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode FX55: LD [I], Vx
void test_FX55_DE() {
    Chip8 chip8{};
    chip8.varRegisters[0] = 1;
    chip8.varRegisters[1] = 2;
    chip8.varRegisters[2] = 3;
    chip8.I = 0x300;
    LOAD_OPCODE(chip8, 0xF255);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.memory[0x300] == 1);
    assert(chip8.memory[0x301] == 2);
    assert(chip8.memory[0x302] == 3);
    std::cout << "Fetch, decode, and execution tests for FX55 passed!" << std::endl;
}

// Fetch, decode, and execute tests for opcode 8XY0: LD Vx, [I]
void test_FX65_DE() {
    Chip8 chip8{};
    chip8.memory[0x300] = 9;
    chip8.memory[0x301] = 8;
    chip8.memory[0x302] = 7;
    chip8.I = 0x300;
    LOAD_OPCODE(chip8, 0xF265);

    decodeAndExecuteInstructions(&chip8);

    assert(chip8.varRegisters[0] == 9);
    assert(chip8.varRegisters[1] == 8);
    assert(chip8.varRegisters[2] == 7);
    std::cout << "Fetch, decode, and execution tests for FX65 passed!" << std::endl;
}

void test_decodeAndExecuteInstructions() {
    test_00E0_DE();
    test_00E0_DE();
    test_00EE_DE();
    test_1NNN_DE();
    test_2NNN_DE();
    test_3XKK_DE();
    test_4XKK_DE();
    test_5XY0_DE();
    test_6XKK_DE();
    test_7XKK_DE();
    test_8XY0_DE();
    test_8XY1_DE();
    test_8XY2_DE();
    test_8XY3_DE();
    test_8XY4_DE();
    test_8XY5_DE();
    test_8XY6_DE();
    test_8XY7_DE();
    test_8XYE_DE();
    test_9XY0_DE();
    test_ANNN_DE();
    test_BNNN_DE();
    test_CXKK_DE();
    test_DXYN_DE();
    test_EX9E_DE();
    test_EXA1_DE();
    test_FX07_DE();
    test_FX0A_DE();
    test_FX15_DE();
    test_FX18_DE();
    test_FX1E_DE();
    test_FX29_DE();
    test_FX33_DE();
    test_FX55_DE();
    test_FX65_DE();
    
    std::cout << "All fetch, decode, and execution instruction tests passed!" << std::endl;
}

void RUN_ALL_CHIP8_TESTS() {
    test_updateTimers();
    test_decodeAndExecuteInstructions();

    std::cout << "All Chip8 tests passed!" << std::endl;
}