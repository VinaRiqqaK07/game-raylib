/**
 * Save System
 *
 * Handles save, load, and delete data, also checking saved data for continue function. Data would be saved in a .dat format file.
 *
 * Usage:
 * 1. Call SaveGameFunc() at every milestone in game progress as checkpoint
 * 2. Check SaveExists() and if it's true then LoadGame() at Continue Button
 * 3. Call DeleteSave() if players start a new game
 *
 */

#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include "save_system.h"
#include "../core/game.h"

/**
 * Savegame structure to store any value that can be saved into .dat file
 */
typedef struct SaveGame
{
    int scene;
    int role;
} SaveGame;

void SaveGameFunc()
{
    FILE *file = fopen("save.dat", "wb");

    if(file == NULL) 
        return ;

    SaveGame data;

    data.scene = game.currentLevel;
    data.role = game.role;

    fwrite(&data, sizeof(SaveGame), 1, file);

    fclose(file);
}

bool LoadGame()
{
    FILE *file = fopen("save.dat", "rb");

    if(file == NULL)
        return false;

    SaveGame data;

    fread(&data, sizeof(SaveGame), 1, file);

    fclose(file);

    game.currentLevel = data.scene;
    game.role = data.role;

    return true;
}

bool SaveExists()
{
    FILE *file = fopen("save.dat", "rb");

    if(file)
    {
        fclose(file);
        return true;
    }

    return false;
}

void DeleteSave()
{
    remove("save.dat");
}