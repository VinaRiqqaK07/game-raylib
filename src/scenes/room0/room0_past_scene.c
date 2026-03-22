#include "raylib.h"
#include "room0_past_scene.h"
#include "../../utils/constants.h"
#include "../../core/game.h"
#include "../../core/scene_manager.h"
#include "../../systems/ui_system.h"

Texture2D introRoomPast;
Rectangle sourceRoomPast;
Rectangle destRoomPast;


void InitRoom0Past()
{
    introRoomPast = LoadTexture("../assets/mainhall_room0_past.jpg");
    
    sourceRoomPast = (Rectangle){0, 0, introRoomPast.width, introRoomPast.height};
    destRoomPast = (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

void UpdateRoom0Past()
{
}

void DrawRoom0Past()
{
    DrawTexturePro(introRoomPast,sourceRoomPast,destRoomPast,(Vector2){0,0},0.0f,WHITE);
    //DrawText("PAST ROOM 0", 200, 150, 20, WHITE);
}

void UnloadRoom0Past()
{
}