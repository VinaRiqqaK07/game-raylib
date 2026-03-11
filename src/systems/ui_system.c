#include "raylib.h"
#include <math.h>
#include "ui_system.h"

bool UIButton(Rectangle rect, const char *text, Color color)
{
    DrawRectangleRec(rect, color);
    
    if(CheckCollisionPointRec(GetMousePosition(), rect))
    {
        DrawRectangleLinesEx(rect, 2, WHITE);
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            return true;
        }
        
    }
    
    DrawText(text, rect.x + 10, rect.y + 10, 20, WHITE);
    
    return false;
    
}


void DrawBlurLine(Vector2 start, Vector2 end, float thickness, Color color)
{
    for(int i = -6; i <= 6; i++)
    {
        float alpha = 1.0f - (fabs(i) / 6.0f);
        Color c = Fade(color, alpha * 0.2f);

        DrawLineEx(
            (Vector2){start.x, start.y + i},
            (Vector2){end.x, end.y + i},
            thickness,
            c
        );
    }
    
    /* USE LIKE THIS
    DrawBlurLine(
        (Vector2){200, 300},
        (Vector2){600, 300},
        2,
        WHITE
    );*/
}