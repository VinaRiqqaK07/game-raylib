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

int titleWidth;
int sloganWidth;
float spacing;
float titleHeight;
float sloganHeight;
float buttonHeight;
float totalHeight;

float startY;
float centerX;
float y;

void InitMenuScene()
{
        spacing = 30;
        titleHeight = 50;
        sloganHeight = 30;
        buttonHeight = 40;
        
        totalHeight = titleHeight + sloganHeight + buttonHeight*2 + spacing * 2;
        
        startY = (SCREEN_HEIGHT/2) - (totalHeight/2);
        centerX = SCREEN_WIDTH/2;
        
        title = "Developed in Time";
        titleWidth = MeasureText(title, 50);
        
        slogan = "Every memory you make becomes the future you live";
        sloganWidth = MeasureText(slogan, 30);
}

void UpdateMenuScene()
{
    
    if(startClicked)
    {
        DeleteSave();
        UnloadMenuScene();     
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
        }            
    }
    
}

void DrawMenuScene()
{
    ClearBackground(BLACK);
    
    // LOGO
    DrawText(title, centerX - titleWidth/2, startY, 50, WHITE);
    y = startY + titleHeight + spacing;
    
    // SLOGAN
    DrawText(slogan, centerX - sloganWidth/2, y, 30, WHITE);
    y += sloganHeight + spacing;
    
    // BUTTON
    Rectangle button = {centerX - 140/2, y, 140, 40};               
    startClicked = UIButton(button, "Start Game", DARKGRAY);
    y += buttonHeight + spacing;
    
    Rectangle buttonContinue = {centerX - 140/2, y, 140, 40};               
    continueClicked = UIButton(buttonContinue, "Continue", DARKGRAY);
    
}

void UnloadMenuScene()
{
    ChangeScene(SELECT_ROLE);
}

