# Chip8
Ensure you have SDL2 installed using the command below.

## Installation
Linux
``` bash
sudo apt-get update
sudo apt-get install libsdl2-dev libsdl2-2.0-0
```

Windows
``` bash
pacman -S mingw-w64-x86_64-SDL2
```

## Compiling
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

``` powershell
g++ -Wall -Wextra -g3 src/Chip8/chip8.cpp src/Display/display.cpp src/Instructions/instructions.cpp 
src/Keypad/keypad.cpp src/Tests/test_instructions.cpp src/Tests/test_chip8.cpp src/main.cpp -o output/chip8 -lmingw32 -lSDL2main -lSDL2
```

## Running ROMs
``` bash
./output/chip8 <Insert ROM Path>
```

NOTE: There are bugs that needs to be fixed.

