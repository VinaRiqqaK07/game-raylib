# Developed in Time

### Description
**Between Two Moments** is a **story-driven cooperative puzzle game** built using **Raylib and C language**. The game is designed to be played by **two players offline on separate screens**. Each player receives **different pieces of information** so the players must **communicate and collaborate** in order to progress through the game and uncover the story.

### Features
- Cooperative puzzle gameplay
- Communication-based mechanics
- Story-driven progression

### Technologies Used
- C Programming Language
- Raylib
- Notepad++ for Raylib

### Project Structure
```
project-folder
│
├── assets/                    # Game assets (images, audio, etc.)
│
├── src/                       # Source code
│   │
│   ├── core/                  # Core game systems (game loop, base engine logic)
│   ├── scenes/                # Scene and level management
│   ├── systems/               # Gameplay systems and puzzle logic
│   └── utils/                 # Helper functions and utilities
│
├── main.c                     # Main entry point of the program
│
├── save.dat                   # Save file for storing game progress
│
├── main.exe                   # Executable generated after build (old version)
└── between-two-moments.exe    # Executable game
```

## How to Run the Game
**Requirement**  
Make sure you have :
- Raylib installed
- Notepadd++ for Raylib

**Steps**
1. Clone this repository
```
git clone https://github.com/VinaRiqqaK07/game-raylib
```
2. Open the project folder
3. Open the file `main.c` using **Notepad++ for Raylib**
4. Press `Fn + F6` or just `F6` to execute the file
5. Run Raylib build using the script provided below or you can configure it yourself :
```
echo > Setup required Environment
echo -------------------------------------
SET PROJECT_NAME=between-two-moments
SET RAYLIB_PATH=C:\raylib\raylib
SET COMPILER_PATH=C:\raylib\w64devkit\bin
ENV_SET PATH=$(COMPILER_PATH)
SET CC=gcc
SET CFLAGS=$(RAYLIB_PATH)\src\raylib.rc.data -s -static -O2 -std=c99 -Wall -I$(RAYLIB_PATH)\src -Iexternal -DPLATFORM_DESKTOP
SET LDFLAGS=-lraylib -lopengl32 -lgdi32 -lwinmm
cd $(CURRENT_DIRECTORY)
echo
echo > Clean latest build
echo ------------------------
cmd /c IF EXIST $(PROJECT_NAME).exe del /F $(PROJECT_NAME).exe
echo
echo > Saving Current File
echo -------------------------
npp_save
echo
echo > Compile program
echo -----------------------
$(CC) --version
$(CC) -o $(PROJECT_NAME).exe main.c core/game.c core/scene_manager.c core/audio_manager.c objects/box.c systems/moments_system.c systems/sequence_system.c systems/connect_minigame.c systems/lighting_system.c scenes/menu_scene.c scenes/selectrole_scene.c scenes/intro_scene.c scenes/ending_scene.c scenes/puzzle1/puzzle1_past_scene.c scenes/puzzle1/puzzle1_future_scene.c scenes/puzzle2/puzzle2_past_scene.c scenes/puzzle2/puzzle2_future_scene.c scenes/puzzle3/puzzle3_future_scene.c scenes/puzzle3/puzzle3_past_scene.c scenes/puzzle4/puzzle4_past_scene.c scenes/puzzle4/puzzle4_future_scene.c systems/save_system.c systems/ui_system.c systems/keypad_system.c systems/keypad_system2.c systems/caption_system.c systems/zoom_system.c systems/wiring_minigame.c $(CFLAGS) $(LDFLAGS)
echo
echo > Reset Environment
echo --------------------------
ENV_UNSET PATH
echo
echo > Execute program
echo -----------------------
cmd /c IF EXIST $(PROJECT_NAME).exe $(PROJECT_NAME).exe
``` 
6. If the compilation is successful, the game executable will be generated and the game will start.

## Development Status
This project is currently under development and may receive future updates including:
- Additional puzzle mechanics
- More story progression
- Improved cooperative gameplay features
- Additional steps for installation
