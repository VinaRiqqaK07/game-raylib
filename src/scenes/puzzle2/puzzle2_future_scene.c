#include "raylib.h"
#include "../../utils/constants.h"
#include "../../core/game.h"
#include "../../core/scene_manager.h"
#include "../../systems/zoom_system.h"
#include "../../systems/keypad_system.h"
#include "../../systems/sequence_system.h"
#include "../../systems/connect_minigame.h"

Texture2D bgPuzzle2Future, shelfFutureP2;

ZoomSystem zoomFutureP2;
ConnectGridPuzzle gridPuzzleFutureP2;

Rectangle shelfAreaP2 = {880, 330, 150, 220};
bool shelfDetailedP2Open = false;

bool IsConnectP2Complete = false;

void InitPuzzle2FutureScene()
{
    bgPuzzle2Future = LoadTexture("../assets/puzzle2/mainhall_room0_future.jpg");
    shelfFutureP2 = LoadTexture("../assets/puzzle2/shelf_puzzle2_future.jpg");
    
    InitZoomSystem(&zoomFutureP2, bgPuzzle2Future);
    InitConnectGrid(&gridPuzzleFutureP2);
}

void UpdatePuzzle2FutureScene()
{
    if (zoomFutureP2.state == ZOOM_IDLE)
    {
        shelfDetailedP2Open = false;
    }
    
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();
        
        if(CheckCollisionPointRec(mouse, shelfAreaP2)&& zoomFutureP2.state == ZOOM_IDLE && !IsConnectP2Complete)
        {
            TriggerZoom(&zoomFutureP2, shelfFutureP2);
            shelfDetailedP2Open = true;
        }
    }
    
    if (shelfDetailedP2Open && !IsConnectP2Complete)
    {
        int offsetX = 400;   // posisi grid di layar (atur sendiri)
        int offsetY = 200;
        int cellSize = 80;

        Node gridPos = GetGridPos(GetMousePosition(), offsetX, offsetY, cellSize);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            TryStartDrag(&gridPuzzleFutureP2, gridPos);
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            UpdateConnectGrid(&gridPuzzleFutureP2, gridPos);
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            gridPuzzleFutureP2.dragging = false;
            gridPuzzleFutureP2.activePair = -1;
        }
        
        IsConnectP2Complete = IsPuzzleComplete(&gridPuzzleFutureP2);

        if (IsConnectP2Complete)
        {
            UnloadTexture(bgPuzzle2Future);
            bgPuzzle2Future = LoadTexture("../assets/puzzle2/mainhall-2_puzzle2_future.jpg");
            InitZoomSystem(&zoomFutureP2, bgPuzzle2Future);
        }
        
        //UpdateConnectGrid(&gridPuzzleFutureP2, gridPos);
    }
    
    
    UpdateZoomSystem(&zoomFutureP2);
    
}


void DrawPuzzle2FutureScene()
{
    ClearBackground(BLACK);
    //DrawTexturePro(introRoomFuture,sourceRoomFuture,destRoomFuture,(Vector2){0,0},0.0f,WHITE);
    //DrawText("FUTURE ROOM 0", 200, 150, 20, WHITE);
    DrawZoomSystem(&zoomFutureP2);
    //DrawText("FUTURE PUZZLE 2", 200, 150, 20, WHITE);
    
    if (shelfDetailedP2Open && zoomFutureP2.state == ZOOMED)
    {
        DrawConnectGrid(&gridPuzzleFutureP2);
    }
    //DrawRectangleRec(shelfArea, WHITE);
    /*
    for (int i = 0; i < 12; i++)
    {
        DrawRectangleRec(telephoneButton[i].bounds, WHITE);
    }*/
    
    //DrawRectangleRec(telephoneArea, WHITE);
    
}

void UnloadPuzzle2FutureScene()
{
    UnloadTexture(bgPuzzle2Future);
}