/**
 * File: intro_scene.c
 * Description:
 * Handles the logic and rendering for Intro Scene before entering gameplay.
 * This room contains background assets (not finished asset yet) with interactable computer area.
 *
 * Responsibilities:
 * - Initialize textures and interactable area
 * - Handle caption render and interactive
 *
 * Dependencies:
 * - ../systems/caption_system.h (for rendering caption)
 *
 *
 */

#include "raylib.h"
#include "intro_scene.h"
#include "../utils/constants.h"
#include "../core/scene_manager.h"
#include "../core/game.h"
#include "../systems/save_system.h"
#include "../systems/caption_system.h"

#define TOTAL_DIALOGUE 6

Texture2D background, computerMouse;
Rectangle sourceBackground, destBackground;
float timerIntro = 0;
int dialogueIndex = 0;

Caption captionIntro;

Rectangle computerRec = {840, 300, 210, 200};
bool computerOpen = false;
bool computerCaptionFinish = false;

void InitIntroScene()
{
    background = LoadTexture("../assets/intro_future.png");
    computerMouse = LoadTexture("../assets/intro-computer.png");
    
    sourceBackground = (Rectangle){0, 0, background.width, background.height};
    destBackground = (Rectangle){0, 0,  SCREEN_WIDTH, SCREEN_HEIGHT};
    
    InitCaptionSystem(&captionIntro);
}

void UpdateIntroScene()
{
    timerIntro += GetFrameTime();
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(GetMousePosition(), computerRec) && timerIntro >= 6.0f)
        {
            computerOpen = true;
            if (!computerCaptionFinish)
            {
                timerIntro = 0.0f;
            }
        }
        else if (computerOpen)
        {
            computerOpen = false;
        }
    }
    
    if (dialogueIndex == 0 && timerIntro >= 0.0f)
    {
        ShowCaption(&captionIntro, "Future : It's... her room. All of it.. Frozen.", 3.0f);
        dialogueIndex++;
    }
    else if (dialogueIndex == 1 && timerIntro >= 3.0f)
    {
        ShowCaption(&captionIntro, "Future : I remember this... and yet it's all wrong.", 3.0f);
        dialogueIndex++;
    }
    else if (dialogueIndex == 2 && timerIntro >= 6.0f)
    {
        ShowCaption(&captionIntro, "Future : I can reach the past... maybe I can save her.", 3.0f);
        dialogueIndex++;
    }
    
    if (computerOpen && !computerCaptionFinish)
    {
        if(dialogueIndex == 3 && timerIntro > 0.5f)
        {
            ShowCaption(&captionIntro, "Future : Can you hear me?", 2.5f);
            dialogueIndex++;
        }
        else if (dialogueIndex == 4 && timerIntro >= 3.0f)
        {
            ShowCaption(&captionIntro, "Past : ...Who is this? Wait... my own voice?", 4.0f);
            dialogueIndex++;
        }
        else if (dialogueIndex == 5 && timerIntro >= 7.0f)
        {
            ShowCaption(&captionIntro, "Future : I'm you... from 20 years ahead. We have to fix things.", 4.0f);
            dialogueIndex++;
            computerCaptionFinish = true;
        }
    }
    UpdateCaption(&captionIntro);
    
    if (computerCaptionFinish && timerIntro >=12.0f)
    {
        game.currentLevel = 1;
        SaveGameFunc();
            
        ChangeScene(SCENE_PUZZLE1);
    }
}

void DrawIntroScene()
{
    ClearBackground(BLACK);
    if (computerOpen)
    {
        DrawTextureEx(computerMouse, (Vector2){SCREEN_WIDTH/2 - computerMouse.width/2 * 0.5, 100}, 0.0f, 0.5f, WHITE);
    }
    else
    {
        DrawTexturePro(background, sourceBackground, destBackground, (Vector2){0,0}, 0.0f, WHITE);
    }
    //DrawRectangleRec(computerRec, WHITE);
    
    DrawCaption(&captionIntro);
}

void UnloadIntroScene()
{
    UnloadTexture(background);
    UnloadTexture(computerMouse);
}