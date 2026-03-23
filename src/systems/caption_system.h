#ifndef CAPTION_SYSTEM_H
#define CAPTION_SYSTEM_H

typedef struct {
    const char *text;
    int textWidth;

    float timer;
    float duration;

    bool active;

    float alpha; 
} Caption;

void InitCaptionSystem(Caption *cap);
void ShowCaption(Caption *cap, const char *text, float duration);
void UpdateCaption(Caption *cap);
void DrawCaption(Caption *cap);

#endif