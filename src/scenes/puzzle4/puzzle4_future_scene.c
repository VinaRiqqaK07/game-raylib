/**
 * File: puzzle3_future_scene.c
 * Description:
 * Handles the logic and rendering for Puzzle 3 FUTURE role Scene.
 * This room contains pictures assets, sequence puzzle, and keypad system.
 *
 * Responsibilities:
 * - Initialize textures.
 * - Handle zoom system, sequence symbol puzzle, and keypad system.
 *
 *
 *
 */
 
#include "raylib.h"
#include "../../utils/constants.h"
#include "../../core/game.h"
#include "../../core/scene_manager.h"
#include "../../systems/keypad_system.h"
#include "../../systems/sequence_system.h"
#include "../../systems/keypad_system2.h"
#include "../../systems/save_system.h"
#include "../../objects/box.h"
#include "../../systems/moments_system.h"

Box itemSheetBox;
bool itemSheetBoxActive = false;

Texture2D bgPuzzle4Future, clue1P4Top, clue1P4Bottom, symbol4P4;

Rectangle keyboardP4Area = {350, 250, 600, 150};

Keypad2 keypadP4;
bool openKeypadP4 = false;

void InitPuzzle4FutureScene()
{
    bgPuzzle4Future = LoadTexture("../assets/puzzle3/future/background_puzzle3_future.png");
    clue1P4Top = LoadTexture("../assets/puzzle4/future/clue1_puzzle4_future.png");
    symbol4P4 = LoadTexture("../assets/puzzle4/future/symbol4_puzzle4_future.png");
    
    itemSheetBox.textureTop = clue1P4Top;
    itemSheetBox.textureBottom = clue1P4Top;
    itemSheetBox.position = (Vector2){100, 400};
    itemSheetBox.rotation = 0.0f;
    itemSheetBox.targetWidth = 600;
    
    keypadP4.correctPassword = "2145";
    keypadP4.maxLength = 4;
    keypadP4.panel = keyboardP4Area;
    
    InitKeypad2(&keypadP4);
}

void UpdatePuzzle4FutureScene()
{
    Rectangle hitbox = {
        itemSheetBox.position.x - 300,
        itemSheetBox.position.y - 200,
        900,
        650
    };

    if(CheckCollisionPointRec(GetMousePosition(), hitbox))
    {
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            itemSheetBoxActive = true;
        }
    }
    
    if(itemSheetBoxActive && !openKeypadP4)
    {
        UpdateBox(&itemSheetBox);
    }
    
    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        itemSheetBoxActive = false;
    }
    
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();
        
        if(CheckCollisionPointRec(mouse, keyboardP4Area) && !keypadP4.passwordCorrect)
        {
            openKeypadP4 = true;
        }
        else if(!CheckCollisionPointRec(mouse, keypadP4.target))
        {
            openKeypadP4 = false;
        }
    }
    UpdateKeypad2(&keypadP4);
    
    if (keypadP4.passwordCorrect && !openKeypadP4)
    {
        //game.currentLevel = 4;
        //SaveGameFunc();
        
        UpdateMoments();
    }
    
}


void DrawPuzzle4FutureScene()
{
    ClearBackground(BLACK);
    
    DrawTexturePro(bgPuzzle4Future, (Rectangle){0, 0, bgPuzzle4Future.width, bgPuzzle4Future.height}, (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, (Vector2){0, 0}, 0.0f, WHITE);
    
    DrawTexturePro(symbol4P4, (Rectangle){0, 0, symbol4P4.width, symbol4P4.height}, (Rectangle){100, 450, 200, (200 * symbol4P4.height/symbol4P4.width)}, (Vector2){0, 0}, 0.0f, WHITE);
    
    //DrawTexturePro(clue1P4Top, (Rectangle){0, 0, clue1P3.width, clue1P3.height}, (Rectangle){130, 100, 700, (700 * clue1P3.height/clue1P3.width)}, (Vector2){0, 0}, 50.0f, WHITE);
    DrawBox(&itemSheetBox);
    
    if (openKeypadP4)
    {
        DrawRectangle(0, 0, SCREEN_WIDTH,SCREEN_HEIGHT, Fade(BLACK, 0.7f));
        DrawKeypad2(&keypadP4);
        DrawText("A = 1\nB = 2\nC = 3", 600, 230, 22, WHITE);
    }
    
    if (keypadP4.passwordCorrect && !openKeypadP4)
    {
        DrawMoments();
    }
}

void UnloadPuzzle4FutureScene()
{
    UnloadTexture(bgPuzzle4Future);
    UnloadTexture(symbol4P4);
    UnloadTexture(clue1P4Top);
}