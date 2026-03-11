#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

typedef enum PlayerRole
{
    ROLE_NONE = 0,
    ROLE_PAST,
    ROLE_FUTURE

} PlayerRole;

typedef struct GameState
{
    PlayerRole role;
    int currentLevel;

    float volume;
    float brightness;

    bool hasSave;

} GameState;

extern GameState game;

void InitGameState();
void ResetGameState();

#endif