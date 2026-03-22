#include "raylib.h"
#include "puzzle1_scene.h"
#include "../core/game.h"
#include "../core/scene_manager.h"
#include "room0/room0_future_scene.h"
#include "room0/room0_past_scene.h"
#include "room1/room1_future_scene.h"
#include "room1/room1_past_scene.h"
#include "room2/room2_future_scene.h"
#include "room2/room2_past_scene.h"
#include "room3/room3_future_scene.h"
#include "room3/room3_past_scene.h"
#include "room4/room4_future_scene.h"
#include "room4/room4_past_scene.h"

#define TOTAL_ROOM 5
int currentRoom = 0;

void (*InitRoomsPast[TOTAL_ROOM])() = {
    InitRoom0Past,
    InitRoom1Past,
    InitRoom2Past,
    InitRoom3Past,
    InitRoom4Past,
};
void (*UpdateRoomsPast[TOTAL_ROOM])() = {
    UpdateRoom0Past,
    UpdateRoom1Past,
    UpdateRoom2Past,
    UpdateRoom3Past,
    UpdateRoom4Past
};
void (*DrawRoomsPast[TOTAL_ROOM])() = {
    DrawRoom0Past,
    DrawRoom1Past,
    DrawRoom2Past,
    DrawRoom3Past,
    DrawRoom4Past
};

void (*InitRoomsFuture[TOTAL_ROOM])() = {
    InitRoom0Future,
    InitRoom1Future,
    InitRoom2Future,
    InitRoom3Future,
    InitRoom4Future
};
void (*UpdateRoomsFuture[TOTAL_ROOM])() = {
    UpdateRoom0Future,
    UpdateRoom1Future,
    UpdateRoom2Future,
    UpdateRoom3Future,
    UpdateRoom4Future
};
void (*DrawRoomsFuture[TOTAL_ROOM])() = {
    DrawRoom0Future,
    DrawRoom1Future,
    DrawRoom2Future,
    DrawRoom3Future,
    DrawRoom4Future
};

void InitPuzzle1Scene()
{
    if (game.role == ROLE_PAST)
    {
        for(int i = 0; i < TOTAL_ROOM; i++)
        {
            InitRoomsPast[i]();
        }
    }
    else if (game.role == ROLE_FUTURE)
    {
        for(int i = 0; i < TOTAL_ROOM; i++)
        {
            InitRoomsFuture[i]();
        }
    }
}

void UpdatePuzzle1Scene()
{
    if (game.role == ROLE_PAST)
    {
        UpdateRoomsPast[currentRoom]();
    
        HandleRoomUI(&currentRoom, TOTAL_ROOM);
    }
    else if (game.role == ROLE_FUTURE)
    {
        UpdateRoomsFuture[currentRoom]();
    
        HandleRoomUI(&currentRoom, TOTAL_ROOM);
    }
}

void DrawPuzzle1Scene()
{
    ClearBackground(BLACK);
    
    if (game.role == ROLE_PAST)
    {
        DrawRoomsPast[currentRoom]();
    
        DrawRoomUI();
    }
    else if (game.role == ROLE_FUTURE)
    {
        DrawRoomsFuture[currentRoom]();
    
        DrawRoomUI();
    }
}


void HandleRoomUI(int *currentRoom, int totalRoom)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int btnWidth = 80;
    int btnHeight = 50;
    int margin = 20;

    Rectangle prevBtn = {
        margin,
        screenHeight/2 - btnHeight/2,
        btnWidth,
        btnHeight
    };

    Rectangle nextBtn = {
        screenWidth - btnWidth - margin,
        screenHeight/2 - btnHeight/2,
        btnWidth,
        btnHeight
    };

    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mouse, prevBtn))
        {
            if (*currentRoom > 0)
                (*currentRoom)--;
        }

        if (CheckCollisionPointRec(mouse, nextBtn))
        {
            if (*currentRoom < totalRoom - 1)
                (*currentRoom)++;
        }
    }
}

void DrawRoomUI()
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int btnWidth = 80;
    int btnHeight = 50;
    int margin = 20;

    // Tombol PREV (kiri)
    Rectangle prevBtn = {
        margin,
        screenHeight/2 - btnHeight/2,
        btnWidth,
        btnHeight
    };

    // Tombol NEXT (kanan)
    Rectangle nextBtn = {
        screenWidth - btnWidth - margin,
        screenHeight/2 - btnHeight/2,
        btnWidth,
        btnHeight
    };

    // DRAW PREV
    DrawRectangleRec(prevBtn, DARKGRAY);
    DrawRectangleLinesEx(prevBtn, 2, WHITE);

    DrawText(
        "<",
        prevBtn.x + btnWidth/2 - 5,
        prevBtn.y + 10,
        30,
        WHITE
    );

    // DRAW NEXT
    DrawRectangleRec(nextBtn, DARKGRAY);
    DrawRectangleLinesEx(nextBtn, 2, WHITE);

    DrawText(
        ">",
        nextBtn.x + btnWidth/2 - 5,
        nextBtn.y + 10,
        30,
        WHITE
    );
}

void UnloadPuzzle1Scene()
{

}