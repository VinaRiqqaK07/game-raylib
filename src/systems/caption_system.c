#include "raylib.h"
#include "../utils/constants.h"

typedef struct {
    const char *text;
    int textWidth;

    float timer;
    float duration;

    bool active;

    float alpha; 
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
        
        //DrawText(cap->text, 100, 200, 30, Fade(BLACK, cap->alpha));
        //DrawText("Draw caption called text active", 200, 150, 20, WHITE);
    }
    
}




