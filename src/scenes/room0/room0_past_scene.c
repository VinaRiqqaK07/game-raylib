#include "raylib.h"
#include "room0_past_scene.h"
#include "../../utils/constants.h"
#include "../../core/game.h"
#include "../../core/scene_manager.h"
#include "../../systems/ui_system.h"
#include "../../systems/zoom_system.h"

Texture2D introRoomPast, candleZoom, roundpicZoom, teasetZoom, telephoneZoom, shelfZoom;
Rectangle sourceRoomPast;
Rectangle destRoomPast;
Rectangle zoomCandle = {450, 250, 100, 100};
Rectangle roundPic = {30, 178, 120, 260};
Rectangle teaSet = {365, 470, 130, 100};
Rectangle telephone = {770, 450, 90, 90};
Rectangle shelf = {880, 330, 150, 200};
    
ZoomSystem zoom;

void InitRoom0Past()
{
    introRoomPast = LoadTexture("../assets/mainhall_room0_past.jpg");
    candleZoom = LoadTexture("../assets/candle_room0_past.jpg");
    roundpicZoom = LoadTexture("../assets/round-pic_room0_past.jpg");
    teasetZoom = LoadTexture("../assets/tea-set_room0_past.jpg");
    telephoneZoom = LoadTexture("../assets/telephone_room0_past.jpg");
    shelfZoom = LoadTexture("../assets/shelf_room0_past.jpg");
    
    sourceRoomPast = (Rectangle){0, 0, introRoomPast.width, introRoomPast.height};
    destRoomPast = (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    
    InitZoomSystem(&zoom, introRoomPast);
    
}

void UpdateRoom0Past()
{
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if(CheckCollisionPointRec(GetMousePosition(), zoomCandle))
        {
            TriggerZoom(&zoom, candleZoom);
        }
        
        if(CheckCollisionPointRec(GetMousePosition(), roundPic))
        {
            TriggerZoom(&zoom, roundpicZoom);
        }
        
        if(CheckCollisionPointRec(GetMousePosition(), teaSet))
        {
            TriggerZoom(&zoom, teasetZoom);
        }
        
        if(CheckCollisionPointRec(GetMousePosition(), telephone))
        {
            TriggerZoom(&zoom, telephoneZoom);
        }
        
        if(CheckCollisionPointRec(GetMousePosition(), shelf))
        {
            TriggerZoom(&zoom, shelfZoom);
        }
        
    }
    
    UpdateZoomSystem(&zoom);
}

void DrawRoom0Past()
{
    //DrawTexturePro(introRoomPast,sourceRoomPast,destRoomPast,(Vector2){0,0},0.0f,WHITE);
    //DrawText("PAST ROOM 0", 200, 150, 20, WHITE);
    
    
    
    
    DrawZoomSystem(&zoom);
    //DrawRectangleRec(telephone, WHITE);
    
}

void UnloadRoom0Past()
{
}