#include "raylib.h"
#include <math.h>
#include "room2_future_scene.h"
#include "../../utils/constants.h"
#include "../../core/game.h"
#include "../../core/scene_manager.h"
#include "../../objects/box.h"

#define SHEETS_COUNT 6
Box sheets[SHEETS_COUNT];

int activeSheetsIndex = -1;
int startXSheet, startYSheet;
Texture2D piano, blockNoteClue, sheet;

void InitRoom2Future()
{
    piano = LoadTexture("../assets/room2/piano_room2_future.png");
    blockNoteClue = LoadTexture("../assets/room2/notes-clue_room2_future.png");
    sheet = LoadTexture("../assets/room2/song-sheets_room2_future.png");
    
    startXSheet = 100;
    startYSheet = 150;
    
    for(int i = 0; i < SHEETS_COUNT; i++)
    {
        float offsetX = GetRandomValue(1, 50);
        float offsetY = GetRandomValue(-50, 50);

        float randomRot = GetRandomValue(-7, 7);
        
        sheets[i].position = (Vector2){startXSheet + (i * 70) + offsetX, startYSheet + offsetY};
        sheets[i].rotation = randomRot;
        sheets[i].textureTop = sheet;
        sheets[i].textureBottom = sheet;
        sheets[i].targetWidth = 120;
    }
}

void UpdateRoom2Future()
{
    for(int i = SHEETS_COUNT - 1; i >= 0; i--)
    {
        Rectangle hitbox = {
            sheets[i].position.x - 120,
            sheets[i].position.y - 120,
            240,
            240
        };

        if(CheckCollisionPointRec(GetMousePosition(), hitbox))
        {
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
            {
                activeSheetsIndex = i;
                break;
            }
        }
    }
    
    for(int i = 0; i < SHEETS_COUNT; i++)
    {
        if(i == activeSheetsIndex)
            if(activeSheetsIndex >= 0 && activeSheetsIndex < SHEETS_COUNT)
                UpdateBox(&sheets[i]);
    }
    
    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        activeSheetsIndex = -1;
    }
}


void DrawRoom2Future()
{
    //DrawText("FUTURE ROOM 2", 200, 150, 20, WHITE);
    
    DrawTextureEx(piano, (Vector2){50, SCREEN_HEIGHT-350}, -5.0f, 0.35f, WHITE);
    DrawTextureEx(blockNoteClue, (Vector2){SCREEN_WIDTH - 400, 100}, 5.0f, 0.3f, WHITE);
    
    for(int i = 0; i < SHEETS_COUNT; i++)
    {
        DrawBox(&sheets[i]);
    }
}

void UnloadRoom2Future()
{

}