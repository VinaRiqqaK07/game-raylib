/**
 * File: menu_scene.c
 * Description:
 * Handles the logic and rendering for Start Menu game.
 * This room contains title and button to start game or continue if saved file exist.
 *
 * Responsibilities:
 * - Initialize text and button positions
 * - Handle button logic interaction for start and continue
 * - Render title and button
 *
 */

#include "menu_scene.h"
#include "../utils/constants.h"
#include "../systems/save_system.h"
#include "../systems/ui_system.h"
#include "../core/scene_manager.h"
#include "../core/game.h"

const char *text;
const char *title;
const char *slogan;
bool startClicked = false;
bool continueClicked = false;
bool loadExist = false;

Texture2D menuBackground, startButton, continueButton;

float spacing;
float buttonHeight;
float totalHeight;

float startY;
float centerX;
float y;

void InitMenuScene()
{
    menuBackground = LoadTexture("../assets/start/main-background.jpeg");
    startButton = LoadTexture("../assets/start/start.jpeg");
    continueButton = LoadTexture("../assets/start/continue.jpeg");
    
    spacing = 30;
    buttonHeight = 70;
        
    totalHeight = buttonHeight*2 + spacing * 2;
        
    startY = (SCREEN_HEIGHT/2) - (totalHeight/2);
    centerX = SCREEN_WIDTH/2;
}

void UpdateMenuScene()
{
    
    if(startClicked)
    {
        DeleteSave();
        ChangeScene(SELECT_ROLE);        
    }
    
    if(continueClicked)
    {
        loadExist = LoadGame();
        if (loadExist)
        {
            if (game.currentLevel == 1)
            {
                ChangeScene(SCENE_PUZZLE1);
            }
            else if (game.currentLevel == 2)
            {
                ChangeScene(SCENE_PUZZLE2);
            }
            else if (game.currentLevel == 3)
            {
                ChangeScene(SCENE_PUZZLE3);
            }
            else if (game.currentLevel == 4)
            {
                ChangeScene(SCENE_PUZZLE4);
            }
        }            
    }
    
}

void DrawMenuScene()
{
    ClearBackground(BLACK);
    
    DrawTexturePro(menuBackground, (Rectangle){0, 0, menuBackground.width, menuBackground.height}, (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, (Vector2){0, 0}, 0.0f, WHITE);
    
    y = startY;
    // BUTTON
    Rectangle button = {centerX - 300/2, y, 300, 70};               
    startClicked = UIButton(button, startButton);
    y += buttonHeight + spacing;
    
    Rectangle buttonContinue = {centerX - 300/2, y, 300, 70};               
    continueClicked = UIButton(buttonContinue, continueButton);
    
}

void UnloadMenuScene()
{
    UnloadTexture(menuBackground);
    UnloadTexture(startButton);
    UnloadTexture(continueButton);
}

