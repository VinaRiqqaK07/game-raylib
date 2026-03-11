#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include "save_system.h"
#include "../core/game.h"

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