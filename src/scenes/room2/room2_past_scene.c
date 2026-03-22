#include "raylib.h"
#include "room2_past_scene.h"
#include "../../utils/constants.h"
#include "../../core/game.h"
#include "../../core/scene_manager.h"
#include "../../systems/ui_system.h"
#include "../../systems/keypad_system.h"

Keypad keypadPanelDrawer;

Texture2D pic1Clue, pic2Clue, TV, flowerVase, vcdTopview;
Rectangle vcdStorage = {280, 420, 245, 245};
Rectangle vcdStorageTarget = {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 200, 230, 350}; 
Rectangle vcdStorageStart = {280, 420, 245, 245};

Rectangle keypadDrawer = {525, 437, 245, 223};

bool openingStorage = false;
bool openStorage = false;

void InitRoom2Past()
{
    pic1Clue = LoadTexture("../assets/room2/pic1-clue_room2_past.png");
    pic2Clue = LoadTexture("../assets/room2/pic2-clue_room2_past.png");
    TV = LoadTexture("../assets/room2/tv_room2_past.png");
    flowerVase = LoadTexture("../assets/room2/flowervase_room2_past.png");
    vcdTopview = LoadTexture("../assets/room2/vcd-topview_room2_past.png");
    
    vcdStorageStart = vcdStorage;
    
    keypadPanelDrawer.correctPassword = "156";
    keypadPanelDrawer.maxLength = 3;
    keypadPanelDrawer.panel = keypadDrawer;
    keypadPanelDrawer.isOpen = false;
    InitKeypad(&keypadPanelDrawer);
}

void UpdateRoom2Past()
{
    UpdateKeypad(&keypadPanelDrawer);
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(GetMousePosition(), vcdStorage) && !keypadPanelDrawer.isOpen)
        {
            openingStorage = true;
        }
        else if (openStorage && !CheckCollisionPointRec(GetMousePosition(), vcdStorageTarget))
        {
            openingStorage = false; 
            openStorage = false; 
        }
    }
    
    if (openingStorage)
    {
        vcdStorage.x += (vcdStorageTarget.x - vcdStorage.x) * 0.1f;
        vcdStorage.y += (vcdStorageTarget.y - vcdStorage.y) * 0.1f;
        vcdStorage.width += (vcdStorageTarget.width - vcdStorage.width) * 0.1f;
        vcdStorage.height += (vcdStorageTarget.height - vcdStorage.height) * 0.1f;
    }
    else
    {
        vcdStorage.x += (vcdStorageStart.x - vcdStorage.x) * 0.1f;
        vcdStorage.y += (vcdStorageStart.y - vcdStorage.y) * 0.1f;
        vcdStorage.width += (vcdStorageStart.width - vcdStorage.width) * 0.1f;
        vcdStorage.height += (vcdStorageStart.height - vcdStorage.height) * 0.1f;
    }
    
    if (vcdStorage.height > 300)
    {
        openStorage = true; 
    }
    else
    {
        openStorage = false;
    }
}

void DrawRoom2Past()
{
    //DrawText("PAST ROOM 2", 200, 150, 20, WHITE);
    
    DrawTextureEx(pic1Clue, (Vector2){40, 100}, 0.0f, 0.25f, WHITE);
    DrawTextureEx(pic2Clue, (Vector2){30, 300}, 0.0f, 0.25f, WHITE);
    DrawTextureEx(TV, (Vector2){280, 150}, 0.0f, 0.3f, WHITE);
    DrawTextureEx(flowerVase, (Vector2){SCREEN_WIDTH - 230, 280}, 0.0f, 0.3f, WHITE);
    
    if (openStorage == true)
    {
        DrawRectangle(0, 0, SCREEN_WIDTH,SCREEN_HEIGHT, Fade(BLACK, 0.7f));
        DrawTextureEx(vcdTopview, (Vector2){SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 200}, 0.0f, 0.3f, WHITE);
        //DrawRectangle(SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 200, 230, 350, WHITE);
    } 
    else
    {
        if (vcdStorage.height > (vcdStorageStart.height + 50))
        {
            DrawRectangleRec(vcdStorage, BROWN);
        }
    }
    
    if (keypadPanelDrawer.isOpen)
    {
        DrawRectangle(0, 0, SCREEN_WIDTH,SCREEN_HEIGHT, Fade(BLACK, 0.7f));
        DrawKeypad(&keypadPanelDrawer);
    }
    
    //DrawRectangleRec(keypadDrawer, WHITE);
}

void UnloadRoom2Past()
{
}