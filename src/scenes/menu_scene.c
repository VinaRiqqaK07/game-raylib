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
#include "../core/audio_manager.h"

const char *text;
const char *title;
const char *slogan;
bool startClicked = false;
bool continueClicked = false;
bool settingsClicked = false;
bool creditsClicked = false;
bool showSettings = false;
bool loadExist = false;

Texture2D menuBackground, startButton, continueButton, settingsButon, creditsButton;

float spacing;
float buttonHeight;
float totalHeight;

float startY;
float centerX;
float y;

Rectangle settingsRectangle;
Rectangle settingsPopup = {SCREEN_WIDTH/2 - 400, 100, 800, 300};

void InitMenuScene()
{
    menuBackground = LoadTexture("../assets/start/main-background.jpeg");
    startButton = LoadTexture("../assets/start/start.jpeg");
    continueButton = LoadTexture("../assets/start/continue.jpeg");
    settingsButon = LoadTexture("../assets/start/settings.jpeg");
    creditsButton = LoadTexture("../assets/start/credits.jpeg");
    
    spacing = 30;
    buttonHeight = 70;
        
    totalHeight = buttonHeight*4 + spacing * 2;
        
    startY = (SCREEN_HEIGHT/2) - (totalHeight/2) + 50;
    centerX = SCREEN_WIDTH/2;
}

void UpdateMenuScene()
{
    
    if(startClicked && !showSettings)
    {
        DeleteSave();
        ChangeScene(SELECT_ROLE);        
    }
    else if(continueClicked && !showSettings)
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
    else if (settingsClicked && !showSettings) 
    {
        showSettings = true;
    }
    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && showSettings && !CheckCollisionPointRec(GetMousePosition(), settingsPopup))
    {
        showSettings = false;
    }
        /*
    if (CheckCollisionPointRec(GetMousePosition(), settingsButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    showSettings = !showSettings;
}
    */
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
    y += buttonHeight + spacing;
    
    settingsRectangle = (Rectangle){centerX - 300/2, y, 300, 70};    
    settingsClicked = UIButton(settingsRectangle, settingsButon);
    y += buttonHeight + spacing;
    
    Rectangle creditsRectangle = {centerX - 300/2, y, 300, 70};    
    creditsClicked = UIButton(creditsRectangle, creditsButton);
    
    if (showSettings) 
    {
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.7f));
        DrawRectangle(centerX - 400, 100, 800, 300, BLACK);

        DrawText("SETTINGS", centerX - MeasureText("SETTINGS", 20)/2, 120, 20, WHITE);

        // Mute Button
        Rectangle muteBtn = {810, 180, 200, 40};

        DrawRectangleRec(muteBtn, GRAY);
        DrawText(IsMuted() ? "Unmute" : "Mute", 820, 190, 20, BLACK);

        if (CheckCollisionPointRec(GetMousePosition(), muteBtn) &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            ToggleMute();
        }

        // Volume Slider (simple)
        float volume = GetVolume();

        Rectangle slider = {300, 190, 500, 20};
        DrawRectangleRec(slider, DARKGRAY);

        DrawRectangle(300, 190, (int)(volume * 500), 20, GREEN);

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse = GetMousePosition();

            if (CheckCollisionPointRec(mouse, slider)) {
                float newVolume = (mouse.x - slider.x) / slider.width;

                if (newVolume < 0) newVolume = 0;
                if (newVolume > 1) newVolume = 1;

                SetVolume(newVolume);
            }
        }
    }
    
}

void UnloadMenuScene()
{
    UnloadTexture(menuBackground);
    UnloadTexture(startButton);
    UnloadTexture(continueButton);
}

