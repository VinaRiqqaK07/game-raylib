#include "scene_manager.h"
#include "../scenes/menu_scene.h" 
#include "../scenes/selectrole_scene.h"
#include "../scenes/intro_scene.h"
#include "../scenes/puzzle1_scene.h"

GameScene currentScene;

void ChangeScene(GameScene newScene)
{
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
            InitPuzzle1Scene();
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
            UpdatePuzzle1Scene();
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
            DrawPuzzle1Scene();
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