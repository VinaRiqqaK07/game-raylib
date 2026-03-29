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

Texture2D bgPuzzle3Future, clue1P3, clue2P3, clue3P3;
Rectangle keyboardP3Area = {350, 250, 600, 150};

Keypad2 keypadP3;
bool openKeypadP3 = false;

void InitPuzzle3FutureScene()
{
    bgPuzzle3Future = LoadTexture("../assets/puzzle3/future/background_puzzle3_future.png");
    clue1P3 = LoadTexture("../assets/puzzle3/future/clue1_puzzle3_future.png");
    clue2P3 = LoadTexture("../assets/puzzle3/future/clue2_puzzle3_future.png");
    clue3P3 = LoadTexture("../assets/puzzle3/future/clue3_puzzle3_future.png");
    
    keypadP3.correctPassword = "895";
    keypadP3.maxLength = 3;
    keypadP3.panel = keyboardP3Area;
    
    InitKeypad2(&keypadP3);
}

void UpdatePuzzle3FutureScene()
{
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();
        
        if(CheckCollisionPointRec(mouse, keyboardP3Area))
        {
            openKeypadP3 = true;
        }
        else if(!CheckCollisionPointRec(mouse, keypadP3.target))
        {
            openKeypadP3 = false;
        }
    }
    UpdateKeypad2(&keypadP3);
    
    if (keypadP3.passwordCorrect && !openKeypadP3)
    {
        game.currentLevel = 4;
        SaveGameFunc();
        
        ChangeScene(SCENE_PUZZLE4);
    }
}


void DrawPuzzle3FutureScene()
{
    ClearBackground(BLACK);
    
    DrawTexturePro(bgPuzzle3Future, (Rectangle){0, 0, bgPuzzle3Future.width, bgPuzzle3Future.height}, (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, (Vector2){0, 0}, 0.0f, WHITE);
    
    DrawTexturePro(clue1P3, (Rectangle){0, 0, clue1P3.width, clue1P3.height}, (Rectangle){130, 100, 700, (700 * clue1P3.height/clue1P3.width)}, (Vector2){0, 0}, 50.0f, WHITE);
    
    DrawTexturePro(clue2P3, (Rectangle){0, 0, clue2P3.width, clue2P3.height}, (Rectangle){400, 400, 300, (300 * clue2P3.height/clue2P3.width)}, (Vector2){0, 0}, 0.0f, WHITE);
    
    DrawTexturePro(clue3P3, (Rectangle){0, 0, clue3P3.width, clue3P3.height}, (Rectangle){970, 380, 300, (300 * clue3P3.height/clue3P3.width)}, (Vector2){0, 0}, 0.0f, WHITE);
    
    if (openKeypadP3)
    {
        DrawRectangle(0, 0, SCREEN_WIDTH,SCREEN_HEIGHT, Fade(BLACK, 0.7f));
        DrawKeypad2(&keypadP3);
        DrawText("Our quest started in the Spider's Den, where\neight legs scurried in the shadows. \nWe then climbed to the Temple of Nine,\nseeking the wisdom of the ancient muses.\nOur journey ended at the Altar of the Open Hand, where \nfive fingers pointed the way home.", 600, 230, 22, WHITE);
    }
    /*
    else
    {
        DrawRectangleRec(keypad.panel, DARKGRAY);
        DrawRectangleLinesEx(keypad.panel, 3, WHITE);    
    }*/
    
    //DrawRectangleRec(keyboardP3Area, WHITE);
}

void UnloadPuzzle3FutureScene()
{
}