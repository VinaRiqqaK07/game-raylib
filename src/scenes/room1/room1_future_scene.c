#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include "room1_future_scene.h"
#include "../../utils/constants.h"
#include "../../core/game.h"
#include "../../core/scene_manager.h"
#include "../../systems/ui_system.h"
#include "../../systems/keypad_system.h"

Keypad keypad;
Texture2D clock, clockFinish, board;

void InitRoom1Future()
{
    clock = LoadTexture("../assets/puzzle1/clock_puzzle1_future.png");
    clockFinish = LoadTexture("../assets/puzzle1/clock-finish_puzzle1_future.png");
    board = LoadTexture("../assets/puzzle1/board_puzzle1_future.png");
    
    keypad.correctPassword = "235";
    keypad.maxLength = 3;
    keypad.panel = (Rectangle){140, 345, 78, 100};
    
    InitKeypad(&keypad);
}

void UpdateRoom1Future()
{
    UpdateKeypad(&keypad);
}


void DrawRoom1Future()
{
    DrawText("FUTURE PUZZLE LEVEL 1", 100, 20, 20, WHITE);
    
    if (keypad.passwordCorrect == true)
    {
        DrawTextureEx(clockFinish, (Vector2){100, 50}, 0.0f, 0.3f, WHITE);
    }else
    {
        DrawTextureEx(clock, (Vector2){100, 50}, 0.0f, 0.3f, WHITE);
    }
    
    DrawTextureEx(board, (Vector2){600, 100}, -5.0f, 0.3f, WHITE);
    
    if (keypad.panel.width > 200)
    {
        DrawRectangle(0, 0, SCREEN_WIDTH,SCREEN_HEIGHT, Fade(BLACK, 0.7f));
        DrawKeypad(&keypad);
    }
    else
    {
        DrawRectangleRec(keypad.panel, DARKGRAY);
        DrawRectangleLinesEx(keypad.panel, 3, WHITE);    
    }
}


void UnloadPuzzle1FutureScene()
{

}