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
    /*SCENE_LEVEL2,
    SCENE_LEVEL3,
    SCENE_LEVEL4,
    SCENE_FINAL*/
} GameScene;

void InitScene(GameScene scene);
void UpdateScene();
void DrawScene();
void ChangeScene(GameScene newScene);
void UnloadScene(GameScene scene);