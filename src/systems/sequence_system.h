#ifndef SEQUENCE_SYSTEM_H
#define SEQUENCE_SYSTEM_H

#define MAX_SEQUENCE 6

typedef struct {
    int sequence[MAX_SEQUENCE];     // correct sequence
    int input[MAX_SEQUENCE];        // input player
    
    int sequenceLength;              // Actual length
    int inputLength;

    float timer;
    float timeout;                 // misalnya 2 detik

    bool solved;
} SymbolPuzzle;

void InitSequencePuzzle(SymbolPuzzle *p, int length);
void AddInput(SymbolPuzzle *p, int value);
void UpdateSequencePuzzle(SymbolPuzzle *p);
bool SequenceComplete(SymbolPuzzle *p);

#endif