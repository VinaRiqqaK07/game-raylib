#ifndef CONNECT_MINIGAME_H
#define CONNECT_MINIGAME_H

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

void InitConnectGrid(ConnectGridPuzzle *p);
Node GetGridPos(Vector2 mouse, int offsetX, int offsetY, int cellSize);
void ClearPath(ConnectGridPuzzle *p, Pair *pair);
void TryStartDrag(ConnectGridPuzzle *p, Node n);
bool IsAdjacent(Node a, Node b);
void UpdateConnectGrid(ConnectGridPuzzle *p, Node n);
void DrawConnectGrid(ConnectGridPuzzle *p);

bool IsGridFull(ConnectGridPuzzle *p);
bool IsPuzzleComplete(ConnectGridPuzzle *p);

#endif