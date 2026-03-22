#pragma once

typedef struct {
    Vector2 position;
    float targetWidth;
    float rotation;
    bool flipped;

    bool dragging;
    Vector2 dragOffset;
    
    Texture2D textureTop;
    Texture2D textureBottom;
} Box;

void UpdateBox(Box *box);

void DrawBox(Box *box);