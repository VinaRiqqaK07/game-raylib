#include "raylib.h"

#define MAX_SEQUENCE 6

typedef struct {
    int sequence[MAX_SEQUENCE];     // correct sequence
    int input[MAX_SEQUENCE];        // input player
    
    int sequenceLength;              // Actual length
    int inputLength;

    float timer;
    float timeout;                 // Timeout sequence

    bool solved;
} SymbolPuzzle;

void InitSequencePuzzle(SymbolPuzzle *p, int length)
{
    // Make sure to init sequence there
    p->sequenceLength = length;
    p->inputLength = 0;
    p->timer = 0.0f;
    p->timeout = 5.0f;

    p->solved = false;
    
    for (int i = 0; i < MAX_SEQUENCE; i++)
    {
        p->input[i] = -1;
    }
}

void AddInput(SymbolPuzzle *p, int value)
{
    if (p->solved) return;
    
    
    if (p->inputLength >= p->sequenceLength)
        return;
    
    if (value != p->sequence[p->inputLength])
    {
        p->inputLength = 0;
        return;
    }

    p->input[p->inputLength] = value;
    p->inputLength++;
    
    p->timer = 0.0f; // reset timer setiap input

    if (p->inputLength == p->sequenceLength)
    {
        p->solved = true;
    }
}

void UpdateSequencePuzzle(SymbolPuzzle *p)
{
    if (p->inputLength > 0 && !p->solved)
    {
        p->timer += GetFrameTime();

        if (p->timer >= p->timeout)
        {
            p->inputLength = 0; // reset input
            p->timer = 0.0f;
        }
    }
}

bool SequenceComplete(SymbolPuzzle *p)
{
    if (p->solved)
    {
        return true;
    }
    return false;
}

/*
void DrawSequencePuzzle(SymbolPuzzle *p, Texture2D solvedTexture)
{
    if (p->solved)
    {
        DrawTexture(solvedTexture, 400, 200, WHITE);
    }
}
*/