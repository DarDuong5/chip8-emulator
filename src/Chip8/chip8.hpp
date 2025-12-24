#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>

#define NUM_OF_V_REGISTERS 16
#define MEMORY_SIZE 4096
#define STACK_SIZE 16
#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32
#define NUM_KEYS 16
#define PC_STARTING_POINT 0x200

const uint8_t FONTSET_START_ADDRESS = 0x050;
const unsigned int FONTSET_SIZE = 80;
constexpr uint8_t fontset[FONTSET_SIZE] = {
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

class Chip8 {
public:
    uint8_t memory[MEMORY_SIZE];
    uint32_t display[DISPLAY_WIDTH][DISPLAY_HEIGHT];
    uint16_t PC; // program counter
    uint16_t I; // index register
    uint16_t stack[STACK_SIZE];
	uint8_t stackPointer;
    uint8_t delayTimer;
    uint8_t soundTimer;
    uint8_t varRegisters[NUM_OF_V_REGISTERS]; // V0 through VF
    uint8_t keyPad[NUM_KEYS];
    uint16_t opcode;
	const char* romPath;
	bool isPaused;
	bool isRunning;

	Chip8() {
		initChip8();
	}

	void loadFontset() {
		for (int i = 0; i < FONTSET_SIZE; i++) {
			memory[FONTSET_START_ADDRESS + i] = fontset[i];
		}
	}

	void clearMemory() {
		for (int i = 0; i < MEMORY_SIZE; i++) {
			memory[i] = 0;
		}
	}

	void clearRegisters() {
		for (int i = 0; i < NUM_OF_V_REGISTERS; i++) {
			varRegisters[i] = 0;
		}
	}

	void clearStack() {
		for (int i = 0; i < STACK_SIZE; i++) {
			stack[i] = 0;
		}
	}

	void clearDisplay() {
		for (int h = 0; h < DISPLAY_HEIGHT; h++) {
			for (int w = 0; w < DISPLAY_WIDTH; w++) {
				display[w][h] = 0;
			}
		}
	}

	void clearKeypad() {
		for (int i = 0; i < NUM_KEYS; i++) {
			keyPad[i] = 0;
		}
	}

	void initChip8() {
		loadFontset();
		clearMemory();
		clearDisplay();
		clearRegisters();
		clearStack();
		clearKeypad();
		PC = PC_STARTING_POINT;
		I = 0;
		stackPointer = 0;
		opcode = 0;
		delayTimer = 0;
		soundTimer = 0;
		isRunning = true;
		isPaused = false;
	}

	void loadROM() {
		std::ifstream file(romPath, std::ios::binary | std::ios::ate);

		if (file.is_open()) {
			std::streampos size = file.tellg();
			char* buffer = new char[size];

			file.seekg(0, std::ios::beg);
			file.read(buffer, size);
			file.close();

			for (long i = 0; i < size; i++) {
				memory[PC_STARTING_POINT + i] = buffer[i];
			}

			free(buffer);
		}
	}
};

void updateTimers(Chip8* chip8);
void fetchInstructions(Chip8* chip8);
void decodeAndExecuteInstructions(Chip8* chip8);

#endif