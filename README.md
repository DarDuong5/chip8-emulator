# Chip8
Ensure you have SDL2 installed using the command below.

## Installation
Linux
``` bash
sudo apt-get update # Update first
sudo apt-get install libsdl2-dev libsdl2-2.0-0
```

Windows (through MSYS2 MinGW64)
``` bash
pacman -Syu # Update first
# If it tells you to close the terminal:
# Close it
# Reopen MINGW64
# Run pacman -Syu again
# Repeat until it says nothing to update.
pacman -S --needed \
    mingw-w64-x86_64-toolchain \
    mingw-w64-x86_64-SDL2
```

## Compiling
Bash
``` bash
g++ -Wall -Wextra -g3 \
    src/Chip8/chip8.cpp \
    src/Display/display.cpp \
    src/Instructions/instructions.cpp \
    src/Keypad/keypad.cpp \
    src/Tests/test_instructions.cpp \
    src/Tests/test_chip8.cpp \
    src/main.cpp \
    -o output/chip8 \
    $(sdl2-config --cflags --libs)
```

Powershell
``` powershell
g++ -Wall -Wextra -g3 src/Chip8/chip8.cpp src/Display/display.cpp src/Instructions/instructions.cpp 
src/Keypad/keypad.cpp src/Tests/test_instructions.cpp src/Tests/test_chip8.cpp src/main.cpp -o output/chip8 -lmingw32 -lSDL2main -lSDL2
```

## Running ROMs
``` bash
./output/chip8 <Insert ROM Path>
```

NOTE: There are bugs that needs to be fixed.

