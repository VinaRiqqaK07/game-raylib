#include "raylib.h"
#include "room3_past_scene.h"
#include "../../utils/constants.h"
#include "../../core/game.h"
#include "../../core/scene_manager.h"
#include "../../systems/ui_system.h"
#include "../../systems/keypad_system.h"

Keypad safeKeypad;

Texture2D clue1, clue2, clue3, safetyBoxClosed, safetyBoxOpen, calendarClue;
Rectangle safeKeypadRectangle = {329, 470, 153, 140};


void InitRoom3Past()
{
    clue1 = LoadTexture("../assets/room3/clue1_room3_past.png");
    clue2 = LoadTexture("../assets/room3/clue2_room3_past.png");
    clue3 = LoadTexture("../assets/room3/clue3_room3_past.png");
    safetyBoxClosed = LoadTexture("../assets/room3/safetybox_room3_past.png");
    safetyBoxOpen = LoadTexture("../assets/room3/safetybox-opened_room3_past.png");
    calendarClue = LoadTexture("../assets/room3/calendar_room3_past.png");
    
    safeKeypad.correctPassword = "527";
    safeKeypad.maxLength = 3;
    safeKeypad.panel = safeKeypadRectangle;
    
    InitKeypad(&safeKeypad);
}

void UpdateRoom3Past()
{
    UpdateKeypad(&safeKeypad);
}

void DrawRoom3Past()
{
    //DrawText("PAST ROOM 3", 200, 150, 20, WHITE);
    
    DrawTextureEx(clue1, (Vector2){100, 70}, -2.0f, 0.25f, WHITE);
    DrawTextureEx(clue2, (Vector2){300, 30}, 7.0f, 0.25f, WHITE);
    DrawTextureEx(clue1, (Vector2){450, 100}, -7.0f, 0.25f, WHITE);
    
    //DrawTextureEx(safetyBoxClosed, (Vector2){80, 400}, 0.0f, 0.3f, WHITE);
    
    DrawTextureEx(calendarClue, (Vector2){SCREEN_WIDTH-450, 70}, 0.0f, 0.25f, WHITE);
    
    if (safeKeypad.passwordCorrect == true)
    {
        DrawTextureEx(safetyBoxOpen, (Vector2){-100, 339}, 0.0f, 0.25f, WHITE);
    }
    else
    {
        DrawTextureEx(safetyBoxClosed, (Vector2){80, 400}, 0.0f, 0.3f, WHITE);
    }
    
    if (safeKeypad.isOpen)
    {
        DrawRectangle(0, 0, SCREEN_WIDTH,SCREEN_HEIGHT, Fade(BLACK, 0.7f));
        DrawKeypad(&safeKeypad);
    }
    
    
    
    //DrawRectangleRec(safeKeypadRectangle,  WHITE);
}

void UnloadRoom3Past()
{
}