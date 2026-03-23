#include "raylib.h"
#include "room0_future_scene.h"
#include "../../utils/constants.h"
#include "../../core/game.h"
#include "../../core/scene_manager.h"

Texture2D introRoomFuture;
Rectangle sourceRoomFuture;
Rectangle destRoomFuture;


void InitRoom0Future()
{
    introRoomFuture = LoadTexture("../assets/mainhall_room0_future.jpg");
    
    sourceRoomFuture = (Rectangle){0, 0, introRoomFuture.width, introRoomFuture.height};
    destRoomFuture = (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

void UpdateRoom0Future()
{
}


void DrawRoom0Future()
{
    DrawTexturePro(introRoomFuture,sourceRoomFuture,destRoomFuture,(Vector2){0,0},0.0f,WHITE);
    //DrawText("FUTURE ROOM 0", 200, 150, 20, WHITE);
}

void UnloadRoom0Future()
{

}