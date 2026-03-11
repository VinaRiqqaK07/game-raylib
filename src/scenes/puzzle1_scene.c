#include "raylib.h"
#include "puzzle1_scene.h"
#include "../utils/constants.h"
#include "../core/game.h"
#include "../core/scene_manager.h"

typedef struct PuzzleBox
{
    Vector2 position;
    float rotation;
    bool flipped;

} PuzzleBox;

PuzzleBox box;

Vector2 center;

void InitPuzzle1Scene()
{
    box.position = (Vector2){400, 300};
    box.rotation = 0;
    box.flipped = false;
    
}

void UpdatePuzzle1Scene()
{
    if (game.role == ROLE_PAST)
    {
        UpdatePuzzle1Past();
    }
    else if (game.role == ROLE_FUTURE)
    {
        UpdatePuzzle1Future();
    }
}

void UpdatePuzzle1Past()
{
    Rectangle boxRect = {box.position.x - 120, box.position.y - 120, 360, 360};
    
    if (CheckCollisionPointRec(GetMousePosition(), boxRect))
    {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            float mouseDelta = GetMouseDelta().x;
            box.rotation += mouseDelta * 0.5f;
            DrawText("Mouse Left Down", 500, 600, 20, WHITE);
        }
        
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            box.flipped = !box.flipped;
        }
        
    }
}

void UpdatePuzzle1Future()
{
    
    
}


void DrawPuzzle1Scene()
{
    ClearBackground(BLACK);
    
    
    
    if (game.role == ROLE_PAST)
    {
        DrawPuzzle1Past();
    }
    else if (game.role == ROLE_FUTURE)
    {
        DrawPuzzle1Future();
    }
    
    
}

void DrawPuzzle1Past()
{
    //DrawText("PAST PUZZLE LEVEL 1", 300, SCREEN_HEIGHT/2, 20, WHITE);
    
    // RECTANGLE ROTATION
    
    Rectangle rect = {box.position.x, box.position.y, 120, 120};

    Vector2 origin = {60, 60};

    float width = 120;
    
    Rectangle drawRect = {box.position.x, box.position.y, width, 120};
    
    if(box.flipped)
        DrawRectanglePro(
            drawRect,
            origin,
            box.rotation,
            BLUE
        );
    else 
        DrawRectanglePro(
            drawRect,
            origin,
            box.rotation,
            RED
        );
    
    center = box.position;
    
}

void DrawPuzzle1Future()
{
    DrawText("FUTURE PUZZLE LEVEL 1", 300, SCREEN_HEIGHT/2, 20, WHITE);
}


void UnloadPuzzle1Scene()
{

}