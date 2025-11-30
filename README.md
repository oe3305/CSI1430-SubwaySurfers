# Subway Surfers Style Runner Game

A 3-lane runner game built with SDL2 and C++.

## Prerequisites

### Required Software
- **w64devkit** - MinGW compiler toolkit
- **Visual Studio Code** (recommended)

### Required Libraries
- **SDL2** development libraries
- **SDL2_mixer** development libraries  
- **SDL2_image** development libraries

## Setup Instructions

### 1. Install w64devkit
1. Download w64devkit from: https://github.com/skeeto/w64devkit/releases
2. Extract to your preferred location (e.g., `C:\w64devkit` or Desktop)

### 2. Install SDL2 Libraries
1. Download SDL2 development libraries:
   - `SDL2-devel-mingw.tar.gz` from https://github.com/libsdl-org/SDL/releases
   - `SDL2_mixer-devel-mingw.tar.gz` from https://github.com/libsdl-org/SDL_mixer/releases  
   - `SDL2_image-devel-mingw.tar.gz` from https://github.com/libsdl-org/SDL_image/releases

2. Extract each and copy files to w64devkit:
   ```
   From: SDL2-x.x.x/x86_64-w64-mingw32/include/SDL2/*
   To: w64devkit/include/SDL2/
   
   From: SDL2-x.x.x/x86_64-w64-mingw32/lib/*
   To: w64devkit/lib/
   
   From: SDL2-x.x.x/x86_64-w64-mingw32/bin/*.dll
   To: w64devkit/bin/
   ```

### 3. Configure VS Code
1. Open the project folder in VS Code
2. Update `.vscode/tasks.json` paths to point to your w64devkit installation
3. Change all instances of the w64devkit path to match your setup

### 4. Build and Run
- **Build**: `Ctrl+Shift+P` → "Tasks: Run Task" → Select build task
- **Or use terminal**: Navigate to project folder and run the generated `.exe`

## Game Controls
- **Left Arrow**: Move left lane
- **Right Arrow**: Move right lane  
- **Q**: Quit game

## Project Structure
- `SDL_Plotter.h/cpp` - Graphics library wrapper for SDL2
- `test.cpp` - Main game (runner with PNG sprites)
- `test3.cpp` - SDL tutorial and learning examples
- `main.cpp` - Original basic examples

## Features
- ✅ 3-lane movement system
- ✅ Obstacle spawning and collision
- ✅ PNG sprite loading with transparency
- ✅ Programmatic sprite generation
- ✅ Game loop with proper timing

## Troubleshooting
- **DLL errors**: Ensure SDL2 DLLs are in same folder as executable
- **Build errors**: Check that w64devkit paths in tasks.json are correct
- **Window not showing**: Check if antivirus is blocking the executable