/**
 * Wiring Minigame
 *
 * Minigame that displays two faced nodes as a wires position.
 * Every wires with the same color need to be connected.
 *
 * Usage:
 * 1. Call InitWiring() once
 * 2. Call UpdateWiring() every frame when particular scene is rendered
 * 3. Call DrawWiring() in render loop
 *
 * 
 */
#include "raylib.h"

typedef struct {
    Vector2 startPos;
    Vector2 endPos;

    Color color;
    bool connected;
} Wire;

typedef struct {
    Wire wires[4];

    int activeWire;   // index yang sedang di-drag
    bool dragging;

    bool completed;
} WiringSystem;

void InitWiring(WiringSystem *ws)
{
    /*
    int slots[4] = {0, 1, 2, 3};

    // shuffle
    for(int i = 3; i > 0; i--)
    {
        int j = GetRandomValue(0, i);

        int temp = slots[i];
        slots[i] = slots[j];
        slots[j] = temp;
    }*/
    
    Color colors[4] = {YELLOW, BLUE, RED, PINK};

    // mapping start → end
    // index: start index
    // value: posisi end index
    int endMapping[4] = {
        2, // YELLOW → posisi 2 (YELLOW di end)
        1, // BLUE   → posisi 1
        0, // RED    → posisi 0
        3  // PINK   → posisi 3
    };

    for(int i = 0; i < 4; i++)
    {
        ws->wires[i].startPos = (Vector2){400, 200 + i * 78};

        ws->wires[i].endPos = (Vector2){
            710,
            200 + endMapping[i] * 78
        };

        ws->wires[i].color = colors[i];
        ws->wires[i].connected = false;
    }

    ws->activeWire = -1;
    ws->dragging = false;
    ws->completed = false;
}

void UpdateWiring(WiringSystem *ws)
{
    Vector2 mouse = GetMousePosition();

    // START DRAG
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        for(int i = 0; i < 4; i++)
        {
            if(CheckCollisionPointCircle(mouse, ws->wires[i].startPos, 20))
            {
                if(!ws->wires[i].connected)
                {
                    ws->activeWire = i;
                    ws->dragging = true;
                }
            }
        }
    }

    // RELEASE
    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        if(ws->dragging && ws->activeWire != -1)
        {
            Wire *w = &ws->wires[ws->activeWire];

            // cek apakah dekat target
            if(CheckCollisionPointCircle(mouse, w->endPos, 30))
            {
                w->connected = true;
            }

            ws->dragging = false;
            ws->activeWire = -1;
        }
    }

    // CHECK COMPLETE
    ws->completed = true;
    for(int i = 0; i < 4; i++)
    {
        if(!ws->wires[i].connected)
        {
            ws->completed = false;
            break;
        }
    }
}

void DrawWiring(WiringSystem *ws)
{
    //DrawRectangleRec((Rectangle){380, 180, 440, 280}, DARKGRAY);
    Vector2 mouse = GetMousePosition();

    for(int i = 0; i < 4; i++)
    {
        Wire w = ws->wires[i];

        // titik kiri
        DrawCircleV(w.startPos, 15, w.color);

        // titik kanan
        DrawCircleV(w.endPos, 15, w.color);

        // garis
        if(w.connected)
        {
            DrawLineEx(w.startPos, w.endPos, 5, w.color);
        }
        else if(ws->dragging && ws->activeWire == i)
        {
            DrawLineEx(w.startPos, mouse, 5, w.color);
        }
    }

    if(ws->completed)
    {
        DrawText("DONE!", 600, 300, 40, GREEN);
    }
}

