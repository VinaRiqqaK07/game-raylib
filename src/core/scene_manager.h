#pragma once

#include "raylib.h"

/**
 * Represents an iterative scene that can be rendered
 */
typedef enum GameScene {
    SCENE_MENU,
    SELECT_ROLE,
    SCENE_INTRO,
    SCENE_PUZZLE1,
    SCENE_PUZZLE2,
    SCENE_PUZZLE3,
    SCENE_PUZZLE4,
    SCENE_ENDING
} GameScene;

GameScene GetCurrentScene();
void InitScene(GameScene scene);
void UpdateScene();
void DrawScene();
void ChangeScene(GameScene newScene);
void UnloadScene(GameScene scene);