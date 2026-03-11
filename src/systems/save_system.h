#pragma once

#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>

void SaveGameFunc();
bool LoadGame();
bool SaveExists();
void DeleteSave();
