#include "raylib.h"
#include <stdlib.h>

#define GRID_SIZE 3
#define MAX_PATH 9

typedef enum {
    CELL_EMPTY,
    CELL_RED,
    CELL_BLUE,
    CELL_PATH_RED,
    CELL_PATH_BLUE
} CellType;

typedef struct {
    int x, y;
} Node;

typedef struct {
    Node start;
    Node end;

    Node path[MAX_PATH];
    int pathLength;

    bool connected;
    CellType pathType;
} Pair;

typedef struct {
    CellType grid[GRID_SIZE][GRID_SIZE];

    Pair pairs[2]; // red + blue
    int pairCount;

    int activePair; // -1 kalau tidak drag
    bool dragging;
}ConnectGridPuzzle;

void InitConnectGrid(ConnectGridPuzzle *p)
{
    // Clear grid
    for(int y = 0; y < GRID_SIZE; y++)
        for(int x = 0; x < GRID_SIZE; x++)
            p->grid[y][x] = CELL_EMPTY;

    p->pairCount = 2;

    // RED
    p->pairs[0].start = (Node){0,0};
    p->pairs[0].end   = (Node){2,1};
    p->pairs[0].pathType = CELL_PATH_RED;
    p->pairs[0].connected = false;
    p->pairs[0].pathLength = 0;

    // BLUE
    p->pairs[1].start = (Node){1,1};
    p->pairs[1].end   = (Node){2,2};
    p->pairs[1].pathType = CELL_PATH_BLUE;
    p->pairs[1].connected = false;
    p->pairs[1].pathLength = 0;

    // Set node di grid
    p->grid[0][0] = CELL_RED;
    p->grid[1][2] = CELL_RED;

    p->grid[1][1] = CELL_BLUE;
    p->grid[2][2] = CELL_BLUE;

    p->activePair = -1;
    p->dragging = false;
}

Node GetGridPos(Vector2 mouse, int offsetX, int offsetY, int cellSize)
{
    Node n;
    n.x = (mouse.x - offsetX) / cellSize;
    n.y = (mouse.y - offsetY) / cellSize;
    return n;
}

void ClearPath(ConnectGridPuzzle *p, Pair *pair)
{
    for(int i = 0; i < pair->pathLength; i++)
    {
        Node n = pair->path[i];

        // jangan hapus node start/end
        if ((n.x == pair->start.x && n.y == pair->start.y) ||
            (n.x == pair->end.x && n.y == pair->end.y))
            continue;

        p->grid[n.y][n.x] = CELL_EMPTY;
    }

    pair->pathLength = 0;
}

void TryStartDrag(ConnectGridPuzzle *p, Node n)
{
    for(int i = 0; i < p->pairCount; i++)
    {
        if (n.x == p->pairs[i].start.x && n.y == p->pairs[i].start.y)
        {
            ClearPath(p, &p->pairs[i]);
            p->activePair = i;
            p->dragging = true;

            // reset path (overwrite)
            p->pairs[i].pathLength = 0;
            p->pairs[i].connected = false;

            return;
        }
    }
}

bool IsAdjacent(Node a, Node b)
{
    return (abs(a.x - b.x) + abs(a.y - b.y)) == 1;
}

void UpdateConnectGrid(ConnectGridPuzzle *p, Node n)
{
    if (!p->dragging || p->activePair == -1) return;

    Pair *pair = &p->pairs[p->activePair];

    Node last;
    if (pair->pathLength == 0)
        last = pair->start;
    else
        last = pair->path[pair->pathLength - 1];

    if (!IsAdjacent(last, n)) return;

    // ❌ Tidak boleh masuk node lain
    if (p->grid[n.y][n.x] == CELL_RED || p->grid[n.y][n.x] == CELL_BLUE)
    {
        // hanya boleh kalau END node pasangan
        if (!(n.x == pair->end.x && n.y == pair->end.y))
            return;
    }

    // overwrite cell lama
    p->grid[n.y][n.x] = pair->pathType;

    pair->path[pair->pathLength++] = n;

    // cek selesai
    if (n.x == pair->end.x && n.y == pair->end.y)
    {
        pair->connected = true;
        p->dragging = false;
        p->activePair = -1;
    }
}

void DrawConnectGrid(ConnectGridPuzzle *p)
{
    int cellSize = 80;
    int offsetX = 400;
    int offsetY = 200;

    for(int y = 0; y < GRID_SIZE; y++)
    {
        for(int x = 0; x < GRID_SIZE; x++)
        {
            Rectangle cell = {
                offsetX + x * cellSize,
                offsetY + y * cellSize,
                cellSize,
                cellSize
            };

            DrawRectangleLinesEx(cell, 2, WHITE);

            switch(p->grid[y][x])
            {
                case CELL_RED: DrawCircle(cell.x+cellSize/2, cell.y+cellSize/2, 10, RED); break;
                case CELL_BLUE: DrawCircle(cell.x+cellSize/2, cell.y+cellSize/2, 10, BLUE); break;
                case CELL_PATH_RED: DrawRectangleRec(cell, Fade(RED, 0.5f)); break;
                case CELL_PATH_BLUE: DrawRectangleRec(cell, Fade(BLUE, 0.5f)); break;
            }
        }
    }
}

bool IsGridFull(ConnectGridPuzzle *p)
{
    for (int y = 0; y < GRID_SIZE; y++)
    {
        for (int x = 0; x < GRID_SIZE; x++)
        {
            if (p->grid[y][x] == CELL_EMPTY)
                return false;
        }
    }
    return true;
}

bool IsPuzzleComplete(ConnectGridPuzzle *p)
{
    for(int i = 0; i < p->pairCount; i++)
    {
        if (!p->pairs[i].connected)
            return false;
    }
    
    // cek grid penuh
    if (!IsGridFull(p))
        return false;
    
    return true;
}



