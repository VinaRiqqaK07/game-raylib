/**
 * File: scene_manager.c
 * Description:
 * Handles all the logic from Initialize, Update, Draw, and Unload for every scene.
 * This file is the one called from main.c, the main bridge between main file with every scene.
 *
 * Responsibilities:
 * - Managing which scene to get Initialized, Updated, and Draw. 
 * - Handle scene switching and unloading scene.
 * 
 *
 * Dependencies:
 * - ../scenes/{all}.h (every header file for scene needed)
 *
 */

#include "scene_manager.h"
#include "game.h"
#include "../scenes/menu_scene.h" 
#include "../scenes/selectrole_scene.h"
#include "../scenes/intro_scene.h"
#include "../scenes/puzzle1_scene.h"
#include "../scenes/puzzle1/puzzle1_past_scene.h"
#include "../scenes/puzzle1/puzzle1_future_scene.h"
#include "../scenes/puzzle2/puzzle2_past_scene.h"
#include "../scenes/puzzle2/puzzle2_future_scene.h"

GameScene currentScene;

void ChangeScene(GameScene newScene)
{
    UnloadScene(currentScene);
    
    currentScene = newScene;
    InitScene(currentScene);
}

void InitScene(GameScene scene)
{
    switch(scene)
    {
        case SCENE_MENU:
            InitMenuScene();
            break;
            
        case SELECT_ROLE:
            InitRoleScene();
            break;
            
        case SCENE_INTRO:
            InitIntroScene();
            break;

        case SCENE_PUZZLE1:
            if (game.role == ROLE_PAST)
            {
                InitPuzzle1PastScene();
            }
            else if (game.role == ROLE_FUTURE)
            {
                InitPuzzle1FutureScene();
            }
            //InitPuzzle1Scene();
            break;
            
        case SCENE_PUZZLE2:
            if (game.role == ROLE_PAST)
            {
                InitPuzzle2PastScene();
            }
            else if (game.role == ROLE_FUTURE)
            {
                InitPuzzle2FutureScene();
            }
            //InitPuzzle1Scene();
            break;
    }
}

void UpdateScene()
{
    switch(currentScene)
    {
        case SCENE_MENU:
            UpdateMenuScene();
            break;
            
        case SELECT_ROLE:
            UpdateRoleScene();
            break;

        case SCENE_INTRO:
            UpdateIntroScene();
            break;

        case SCENE_PUZZLE1:
            if (game.role == ROLE_PAST)
            {
                UpdatePuzzle1PastScene();
            }
            else if (game.role == ROLE_FUTURE)
            {
                UpdatePuzzle1FutureScene();
            }
            //UpdatePuzzle1Scene();
            break;
            
        case SCENE_PUZZLE2:
            if (game.role == ROLE_PAST)
            {
                UpdatePuzzle2PastScene();
            }
            else if (game.role == ROLE_FUTURE)
            {
                UpdatePuzzle2FutureScene();
            }
            //UpdatePuzzle1Scene();
            break;

        /*case SCENE_LEVEL2:
            UpdateLevel2Scene();
            break;

        case SCENE_LEVEL3:
            UpdateLevel3Scene();
            break;

        case SCENE_LEVEL4:
            UpdateLevel4Scene();
            break;

        case SCENE_FINAL:
            UpdateFinalScene();
            break;*/
    }
}

void DrawScene()
{
    switch(currentScene)
    {
        case SCENE_MENU:
            DrawMenuScene();
            break;
            
        case SELECT_ROLE:
            DrawRoleScene();
            break;

        case SCENE_INTRO:
            DrawIntroScene();
            break;

        case SCENE_PUZZLE1:
            if (game.role == ROLE_PAST)
            {
                DrawPuzzle1PastScene();
            }
            else if (game.role == ROLE_FUTURE)
            {
                DrawPuzzle1FutureScene();
            }
            //DrawPuzzle1Scene();
            break;
            
        case SCENE_PUZZLE2:
            if (game.role == ROLE_PAST)
            {
                DrawPuzzle2PastScene();
            }
            else if (game.role == ROLE_FUTURE)
            {
                DrawPuzzle2FutureScene();
            }
            //DrawPuzzle1Scene();
            break;

        /*case SCENE_LEVEL2:
            DrawLevel2Scene();
            break;

        case SCENE_LEVEL3:
            DrawLevel3Scene();
            break;

        case SCENE_LEVEL4:
            DrawLevel4Scene();
            break;

        case SCENE_FINAL:
            DrawFinalScene();
            break;*/
    }
}

void UnloadScene(GameScene scene)
{
    switch(scene)
    {
        case SCENE_MENU:
            UnloadMenuScene();
            break;
            
        case SELECT_ROLE:
            UnloadRoleScene();
            break;
            
        case SCENE_INTRO:
            UnloadIntroScene();
            break;

        case SCENE_PUZZLE1:
            if (game.role == ROLE_PAST)
            {
                UnloadPuzzle1PastScene();
            }
            else if (game.role == ROLE_FUTURE)
            {
                UnloadPuzzle1FutureScene();
            }
            //UnloadPuzzle1Scene();
            break;
            
        case SCENE_PUZZLE2:
            if (game.role == ROLE_PAST)
            {
                UnloadPuzzle2PastScene();
            }
            else if (game.role == ROLE_FUTURE)
            {
                UnloadPuzzle2FutureScene();
            }
            //UnloadPuzzle1Scene();
            break;
    }
}