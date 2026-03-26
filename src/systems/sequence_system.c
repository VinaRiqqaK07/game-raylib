#include "raylib.h"

#define MAX_SEQUENCE 5

typedef struct {
    int sequence[MAX_SEQUENCE];     // correct sequence
    int input[MAX_SEQUENCE];        // input player
    int inputLength;

    float timer;
    float timeout;                 // misalnya 2 detik

    bool solved;
} SymbolPuzzle;

void InitSequencePuzzle(SymbolPuzzle *p)
{
    // Make sure to init sequence there

    p->inputLength = 0;
    p->timer = 0.0f;
    p->timeout = 2.0f;

    p->solved = false;
}

void AddInput(SymbolPuzzle *p, int value)
{
    if (p->solved) return;

    p->input[p->inputLength] = value;
    p->inputLength++;

    p->timer = 0.0f; // reset timer setiap input

    // ❌ cek salah langsung
    for (int i = 0; i < p->inputLength; i++)
    {
        if (p->input[i] != p->sequence[i])
        {
            p->inputLength = 0; // reset
            return;
        }
    }

    // ✅ kalau sudah lengkap
    if (p->inputLength == MAX_SEQUENCE)
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