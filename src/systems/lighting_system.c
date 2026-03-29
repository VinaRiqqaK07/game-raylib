#include "lighting_system.h"
#include "raymath.h"
#include "rlgl.h"

#define RLGL_SRC_ALPHA  0x0302
#define RLGL_MIN        0x8007
#define RLGL_MAX        0x8008

// ================= WALL =================
void InitWalls(WallSystem *ws)
{
    ws->wallCount = 0;
}

void AddWall(WallSystem *ws, Rectangle rect)
{
    if (ws->wallCount < MAX_WALLS)
    {
        ws->walls[ws->wallCount++] = rect;
    }
}

// ================= LIGHT =================
static void MoveLight(LightSystem *ls, Vector2 pos)
{
    ls->position = pos;
    ls->dirty = true;

    ls->bounds = (Rectangle){
        pos.x - ls->radius,
        pos.y - ls->radius,
        ls->radius * 2,
        ls->radius * 2
    };
}

// shadow edge
static void ComputeShadow(LightSystem *ls, Vector2 sp, Vector2 ep)
{
    if (ls->shadowCount >= MAX_SHADOWS) return;

    float extension = ls->radius * 2;

    Vector2 spDir = Vector2Normalize(Vector2Subtract(sp, ls->position));
    Vector2 epDir = Vector2Normalize(Vector2Subtract(ep, ls->position));

    Vector2 spProj = Vector2Add(sp, Vector2Scale(spDir, extension));
    Vector2 epProj = Vector2Add(ep, Vector2Scale(epDir, extension));

    ShadowQuad *s = &ls->shadows[ls->shadowCount++];

    s->vertices[0] = sp;
    s->vertices[1] = ep;
    s->vertices[2] = epProj;
    s->vertices[3] = spProj;
}

// generate shadow dari semua wall
static void GenerateShadows(LightSystem *ls, WallSystem *ws)
{
    ls->shadowCount = 0;
    ls->valid = true;

    for (int i = 0; i < ws->wallCount; i++)
    {
        Rectangle r = ws->walls[i];

        if (CheckCollisionPointRec(ls->position, r))
        {
            ls->valid = false;
            return;
        }

        if (!CheckCollisionRecs(ls->bounds, r)) continue;

        Vector2 p1 = {r.x, r.y};
        Vector2 p2 = {r.x + r.width, r.y};
        Vector2 p3 = {r.x + r.width, r.y + r.height};
        Vector2 p4 = {r.x, r.y + r.height};

        if (ls->position.y > p2.y) ComputeShadow(ls, p1, p2);
        if (ls->position.x < p3.x) ComputeShadow(ls, p2, p3);
        if (ls->position.y < p3.y) ComputeShadow(ls, p3, p4);
        if (ls->position.x > p1.x) ComputeShadow(ls, p4, p1);

        // box itself
        ShadowQuad *s = &ls->shadows[ls->shadowCount++];
        s->vertices[0] = p1;
        s->vertices[1] = p4;
        s->vertices[2] = p3;
        s->vertices[3] = p2;
    }
}

// render mask
static void DrawLightMask(LightSystem *ls)
{
    BeginTextureMode(ls->mask);
        ClearBackground(WHITE);

        rlSetBlendFactors(RLGL_SRC_ALPHA, RLGL_SRC_ALPHA, RLGL_MIN);
        rlSetBlendMode(BLEND_CUSTOM);

        if (ls->valid)
        {
            DrawCircleGradient(
                ls->position.x,
                ls->position.y,
                ls->radius,
                Fade(WHITE, 0),
                WHITE
            );
        }

        rlDrawRenderBatchActive();

        rlSetBlendMode(BLEND_ALPHA);
        rlSetBlendFactors(RLGL_SRC_ALPHA, RLGL_SRC_ALPHA, RLGL_MAX);
        rlSetBlendMode(BLEND_CUSTOM);

        for (int i = 0; i < ls->shadowCount; i++)
        {
            DrawTriangleFan(ls->shadows[i].vertices, 4, WHITE);
        }

        rlDrawRenderBatchActive();
        rlSetBlendMode(BLEND_ALPHA);

    EndTextureMode();
}

// ================= PUBLIC =================

void InitLighting(LightSystem *ls, float x, float y, float radius)
{
    ls->position = (Vector2){x, y};
    ls->radius = radius;

    ls->mask = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    ls->dirty = true;
    ls->valid = false;
}

bool CheckLightCollision(Vector2 pos, float radius, WallSystem *ws)
{
    for (int i = 0; i < ws->wallCount; i++)
    {
        if (CheckCollisionCircleRec(pos, radius, ws->walls[i]))
        {
            return true;
        }
    }
    return false;
}

void UpdateLighting(LightSystem *ls, WallSystem *ws)
{
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();

        // coba posisi baru
        if (!CheckLightCollision(mouse, 10, ws)) // 10 = radius collider kecil
        {
            MoveLight(ls, mouse);
        }
    }

    if (!ls->dirty) return;

    ls->dirty = false;

    GenerateShadows(ls, ws);
    DrawLightMask(ls);
}

void DrawLighting(LightSystem *ls)
{
    DrawTextureRec(
        ls->mask.texture,
        (Rectangle){0, 0, (float)GetScreenWidth(), -(float)GetScreenHeight()},
        (Vector2){0,0},
        BLACK
    );

    DrawCircleV(ls->position, 8, YELLOW);
}