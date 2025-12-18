#ifndef chip8
#define chip8

#include <iostream>
#include <cstdint>
#include <fstream>
#include <chrono>
#include <random>

#define NUM_OF_V_REGISTERS 16
#define MEMORY_SIZE 4096
#define NUM_OF_STACK_LEVELS 16
#define NUM_OF_KEYS 16
#define MONOCHROME_DISPLAY_SIZE 64*32

const unsigned int FONTSET_SIZE = 80;

class Chip8 {
    Chip8() : randGen(std::chrono::system_clock::now().time_since_epoch().count()) {
        randByte = std::uniform_int_distribution<uint8_t>(0, 255U);
    }
    
public:
    // V0 to VF
    uint8_t registers[NUM_OF_V_REGISTERS]{};
    // in bytes
    uint8_t memory[MEMORY_SIZE]{};
    // program counter
    uint16_t pc{};
    uint16_t index{};
    uint8_t stackPtr{};
    uint16_t stack[NUM_OF_STACK_LEVELS]{};
    uint8_t delayTimer{};
    uint8_t soundTimer{};
    // 0 to F
    uint16_t keyPad[NUM_OF_KEYS]{};
    uint32_t video[MONOCHROME_DISPLAY_SIZE]{};
    uint16_t opcode;

    std::default_random_engine randGen;
    std::uniform_int_distribution<uint8_t> randByte;

    void loadROM(char const* filename);
};

uint8_t fontset[FONTSET_SIZE] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

#endif