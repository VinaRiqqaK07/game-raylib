#include "raylib.h"
#include "room0_future_scene.h"
#include "../../utils/constants.h"
#include "../../core/game.h"
#include "../../core/scene_manager.h"
#include "../../systems/zoom_system.h"
#include "../../systems/keypad_system.h"

Texture2D introRoomFuture, tiltedPic, roundSafe, roundSafeKeypad;
Rectangle sourceRoomFuture;
Rectangle destRoomFuture;

Rectangle tiltedPicArea = {320, 220, 140, 210};
Rectangle roundKeypadArea = {845, 325, 40, 65};

bool tiltedPicShoved = false;
bool roundSafeShowed = false;
bool keypadShowed = false;

ZoomSystem zoomFuture;
Keypad keypadRoundSafe;

void InitRoom0Future()
{
    introRoomFuture = LoadTexture("../assets/room0/mainhall-0_room0_future.jpg");
    tiltedPic = LoadTexture("../assets/room0/tilted-pic_room0_future.png");
    roundSafe = LoadTexture("../assets/room0/roundsafe-closed_room0_future.jpg");
    roundSafeKeypad = LoadTexture("../assets/room0/roundsafekeypad_room0_future.jpg");
    
    sourceRoomFuture = (Rectangle){0, 0, introRoomFuture.width, introRoomFuture.height};
    destRoomFuture = (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    
    InitZoomSystem(&zoomFuture, introRoomFuture);
    
    keypadRoundSafe.correctPassword = "617";
    keypadRoundSafe.maxLength = 3;
    keypadRoundSafe.panel = (Rectangle){140, 345, 78, 100};
    keypadRoundSafe.opening = true;
    keypadRoundSafe.isOpen = true;
    
    InitKeypad(&keypadRoundSafe);
}

void UpdateRoom0Future()
{
    if (zoomFuture.state == ZOOM_IDLE)
    {
        roundSafeShowed = false;
        keypadShowed = false;
    }
    
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();
        
        if(CheckCollisionPointRec(mouse, tiltedPicArea)&& zoomFuture.state == ZOOM_IDLE)
        {
            TriggerZoom(&zoomFuture, roundSafe);
            roundSafeShowed = true;
        }
        else if(CheckCollisionPointRec(mouse, (Rectangle){380, 0, 640, 680}) && !tiltedPicShoved && roundSafeShowed)
        {
            tiltedPicShoved = true;
        }
        else if(CheckCollisionPointRec(mouse, roundKeypadArea) && tiltedPicShoved && roundSafeShowed)
        {
            zoomFuture.state = ZOOM_IDLE;
            TriggerZoom(&zoomFuture, roundSafeKeypad);
            keypadShowed = true;
        }
        
    }
    
    UpdateZoomSystem(&zoomFuture);
    if (keypadShowed)
    {
        UpdateKeypad(&keypadRoundSafe);
        if (keypadRoundSafe.passwordCorrect)
        {
            roundSafe = LoadTexture("../assets/room0/roundsafe-open_room0_future.jpg");
            InitZoomSystem(&zoomFuture, introRoomFuture);
        }
    }
}


void DrawRoom0Future()
{
    //DrawTexturePro(introRoomFuture,sourceRoomFuture,destRoomFuture,(Vector2){0,0},0.0f,WHITE);
    //DrawText("FUTURE ROOM 0", 200, 150, 20, WHITE);
    DrawZoomSystem(&zoomFuture);
    
    if (!tiltedPicShoved && roundSafeShowed && zoomFuture.state == ZOOMED)
    {
        DrawTexturePro(tiltedPic, (Rectangle){0, 0, tiltedPic.width, tiltedPic.height}, (Rectangle){380, 0, 640, 680}, (Vector2){0,0}, 3.0f,WHITE);
    }
    else if (keypadShowed && zoomFuture.state == ZOOMED && !keypadRoundSafe.passwordCorrect)
    {
        DrawKeypad(&keypadRoundSafe);
        DrawRectangleRec(roundKeypadArea, WHITE);
    }
    //DrawRectangleRec(tiltedPicArea, WHITE);
    
}

void UnloadRoom0Future()
{

}