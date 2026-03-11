#include "raylib.h"
#include "game.h"

GameState game;

void InitGameState()
{
    game.role = ROLE_NONE;
    game.currentLevel = 0;

    game.volume = 1.0f;
    game.brightness = 1.0f;

    game.hasSave = false;
}

void ResetGameState()
{
    game.role = ROLE_NONE;
    game.currentLevel = 0;
}