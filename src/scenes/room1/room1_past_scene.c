#include "raylib.h"
#include "room1_past_scene.h"
#include "../../utils/constants.h"
#include "../../core/game.h"
#include "../../core/scene_manager.h"
#include "../../systems/ui_system.h"
#include "../../objects/box.h"

#define BOX_COUNT 3
Box boxes[BOX_COUNT];
int activeBoxIndex = -1;

Texture2D table, simbol1, simbol2, simbol3, digit1, digit2, digit3, noteclue;

void InitRoom1Past()
{
    table = LoadTexture("../assets/puzzle1/table_puzzle1_past.png");
    noteclue = LoadTexture("../assets/puzzle1/noteclue_puzzle1_past.png");
    
    simbol1 = LoadTexture("../assets/puzzle1/simbol1_puzzle1_past.png");
    digit1 = LoadTexture("../assets/puzzle1/number2_puzzle1_past.png");
    
    simbol2 = LoadTexture("../assets/puzzle1/simbol2_puzzle1_past.png");
    digit2 = LoadTexture("../assets/puzzle1/number3_puzzle1_past.png");
    
    simbol3 = LoadTexture("../assets/puzzle1/simbol3_puzzle1_past.png");
    digit3 = LoadTexture("../assets/puzzle1/number5_puzzle1_past.png");
    
    // INIT BOX 
    boxes[0].position = (Vector2){208,276};
    boxes[0].rotation = -10.0f;
    boxes[0].textureTop = simbol1;
    boxes[0].textureBottom = digit1;
    
    boxes[1].position = (Vector2){434,458};
    boxes[1].rotation = 6.0f;
    boxes[1].textureTop = simbol2;
    boxes[1].textureBottom = digit2;
    
    boxes[2].position = (Vector2){602,246};
    boxes[2].rotation = -4.0f;
    boxes[2].textureTop = simbol3;
    boxes[2].textureBottom = digit3;
    
    for(int i = 0; i < BOX_COUNT; i++)
    {
        boxes[i].targetWidth = 180;
    }
}

void UpdateRoom1Past()
{
    for(int i = BOX_COUNT-1; i >= 0; i--)
    {
        Rectangle hitbox = {
            boxes[i].position.x - 120,
            boxes[i].position.y - 120,
            240,
            240
        };

        if(CheckCollisionPointRec(GetMousePosition(), hitbox))
        {
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
            {
                activeBoxIndex = i;
                break;
            }
        }
    }
    
    for(int i = 0; i < BOX_COUNT; i++)
    {
        if(i == activeBoxIndex)
            UpdateBox(&boxes[i]);
    }
    
    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        activeBoxIndex = -1;
    }
}

void DrawRoom1Past()
{
    DrawText("PAST PUZZLE LEVEL 1", 200, 150, 20, WHITE);
    
    //DrawTexture(table, 100, 100, WHITE);
    DrawTextureEx(table, (Vector2){50, 100}, -5.0f, 0.5f, WHITE);
    DrawTextureEx(noteclue, (Vector2){850, 30}, 5.0f, 0.3f, WHITE);
    
    for(int i = 0; i < BOX_COUNT; i++)
    {
        DrawBox(&boxes[i]);
    }
}

void UnloadPuzzle1PastScene()
{
    UnloadTexture(table);
    UnloadTexture(noteclue);
    
    UnloadTexture(simbol1);
    UnloadTexture(simbol2);
    UnloadTexture(simbol3);
    UnloadTexture(digit1);
    UnloadTexture(digit2);
    UnloadTexture(digit3);
}