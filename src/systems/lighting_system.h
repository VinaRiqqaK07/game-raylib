#ifndef LIGHTING_SYSTEM_H
#define LIGHTING_SYSTEM_H

#include "raylib.h"

#define MAX_WALLS 32
#define MAX_SHADOWS 128

typedef struct {
    Vector2 vertices[4];
} ShadowQuad;

typedef struct {
    Vector2 position;
    float radius;

    RenderTexture2D mask;

    ShadowQuad shadows[MAX_SHADOWS];
    int shadowCount;

    Rectangle bounds;

    bool dirty;
    bool valid;
} LightSystem;

typedef struct {
    Rectangle walls[MAX_WALLS];
    int wallCount;
} WallSystem;

// CORE
void InitLighting(LightSystem *ls, float x, float y, float radius);
bool CheckLightCollision(Vector2 pos, float radius, WallSystem *ws);
void UpdateLighting(LightSystem *ls, WallSystem *ws);
void DrawLighting(LightSystem *ls);

// WALL
void InitWalls(WallSystem *ws);
void AddWall(WallSystem *ws, Rectangle rect);

#endif