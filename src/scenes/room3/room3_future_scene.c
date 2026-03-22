#include "raylib.h"
#include "room3_future_scene.h"
#include "../../utils/constants.h"
#include "../../core/game.h"
#include "../../core/scene_manager.h"
#include "../../objects/box.h"

#define PICTURE_COUNT 7
Box picturesClue[PICTURE_COUNT];


int activePicturesIndex = -1;

Texture2D pictureclueTop, pictureclueBottom;

void InitRoom3Future()
{
    pictureclueTop = LoadTexture("../assets/room3/pictureclue_room3_future.png");
    pictureclueBottom = LoadTexture("../assets/room3/pictureclue-bottom_room3_future.png");
    
    for(int i = 0; i < PICTURE_COUNT; i++)
    {
        float offsetX = GetRandomValue(-(SCREEN_WIDTH/3), SCREEN_WIDTH/3);
        float offsetY = GetRandomValue(-(SCREEN_HEIGHT/3), SCREEN_HEIGHT/3);

        float randomRot = GetRandomValue(-7, 7);
        
        picturesClue[i].position = (Vector2){SCREEN_WIDTH/2 + offsetX, SCREEN_HEIGHT/2 + offsetY};
        picturesClue[i].rotation = randomRot;
        picturesClue[i].textureTop = pictureclueTop;
        picturesClue[i].textureBottom = pictureclueBottom;
        picturesClue[i].targetWidth = 400;
    }
}

void UpdateRoom3Future()
{
    for(int i = PICTURE_COUNT - 1; i >= 0; i--)
    {
        Rectangle hitbox = {
            picturesClue[i].position.x - 120,
            picturesClue[i].position.y - 120,
            240,
            240
        };

        if(CheckCollisionPointRec(GetMousePosition(), hitbox))
        {
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
            {
                activePicturesIndex = i;
                break;
            }
        }
    }
    
    for(int i = 0; i < PICTURE_COUNT; i++)
    {
        if(i == activePicturesIndex)
            if(activePicturesIndex >= 0 && activePicturesIndex < PICTURE_COUNT)
                UpdateBox(&picturesClue[i]);
    }
    
    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        activePicturesIndex = -1;
    }
}


void DrawRoom3Future()
{
    //DrawText("FUTURE ROOM 3", 200, 150, 20, WHITE);
    
    for(int i = 0; i < PICTURE_COUNT; i++)
    {
        DrawBox(&picturesClue[i]);
    }
}

void UnloadRoom3Future()
{

}