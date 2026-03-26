/**
 * Caption System
 *
 * Displays narrative text with fade-in and fade-out animation.
 *
 * Usage:
 * 1. Call InitCaptionSystem() once
 * 2. Call ShowCaption() to trigger a caption
 * 3. Call UpdateCaption() every frame
 * 4. Call DrawCaption() in render loop
 *
 * Notes:
 * - Uses timer-based animation
 * - Only one caption active at a time
 */
#include "raylib.h"
#include "../utils/constants.h"

/**
 * Represents a caption structure that supports fade-in
 * fade-out animation and duration.
 */
typedef struct {
    const char *text;   // Text to be rendered
    int textWidth;      // Width of the text

    float timer;        // text timer/inner clock
    float duration;     // the duration text will be displayed

    bool active;        // Is caption active or not

    float alpha;        // Text visibility
} Caption;

void InitCaptionSystem(Caption *cap)
{
    cap->text = "";
    cap->textWidth = MeasureText(cap->text, 30);
    cap->duration = 0.0f;
    cap->timer = 0.0f;
    cap->active = false;
    cap->alpha = 0.0f;
}

void ShowCaption(Caption *cap, const char *text, float duration)
{
    cap->text = text;
    cap->textWidth = MeasureText(text, 30);
    cap->duration = duration;
    cap->timer = 0;
    cap->active = true;
    cap->alpha = 0.0f;
}

void UpdateCaption(Caption *cap)
{
    if (cap->active)
    {
        cap->timer += GetFrameTime();
        
        if (cap->timer < 0.5f)
            cap->alpha = cap->timer / 0.5f;
        else if (cap->timer > cap->duration - 0.5f)
            cap->alpha = (cap->duration - cap->timer) / 0.5f;
        else 
            cap->alpha = 1.0f;
        
        if (cap->timer >= cap->duration)
            cap->active = false;
        
        //DrawText("update caption called text active", 300, 150, 20, WHITE);
    }
}

void DrawCaption(Caption *cap)
{
    if (cap->active)
    {
        DrawRectangle(0, SCREEN_HEIGHT - 150, SCREEN_WIDTH, 150, Fade(WHITE, 0.6f * cap->alpha));
        
        
        DrawText(cap->text, SCREEN_WIDTH/2 - (cap->textWidth)/2, SCREEN_HEIGHT - 100, 30, Fade(BLACK, cap->alpha));
       
        //DrawTextRec(GetFontDefault(), cap->text, (Rectangle){SCREEN_WIDTH/2 - 250, SCREEN_HEIGHT - 100, SCREEN_WIDTH/2, 120}, 30, 2, true, Fade(BLACK, cap->alpha));
        
        //DrawText(cap->text, 100, 200, 30, Fade(BLACK, cap->alpha));
        //DrawText("Draw caption called text active", 200, 150, 20, WHITE);
    }
    
}




