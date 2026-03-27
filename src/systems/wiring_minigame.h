#ifndef WIRING_MINIGAME_H
#define WIRING_MINIGAME_H

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

void InitWiring(WiringSystem *ws);
void UpdateWiring(WiringSystem *ws);
void DrawWiring(WiringSystem *ws);

#endif