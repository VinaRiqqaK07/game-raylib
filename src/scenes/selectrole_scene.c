#include "raylib.h"
#include "selectrole_scene.h"
#include "../utils/constants.h"
#include "../core/game.h"
#include "../core/scene_manager.h"
#include "../systems/ui_system.h"


int selectedRole;
int pastTextWidth;
int futureTextWidth;
const char *pastText;
const char *futureText;
bool buttonClicked;

void InitRoleScene()
{
    selectedRole = 0;
    pastText = "PAST";
    futureText = "FUTURE";
    
    pastTextWidth = MeasureText(pastText, 40);
    futureTextWidth = MeasureText(futureText, 40);
    
}

void UpdateRoleScene()
{

}

void DrawRoleScene()
{
    ClearBackground(BLACK);
    
    switch(selectedRole)
    {
        case 0:
            ShowSelection();
            break;
            
        case 1:
            ShowPast();
            break;
            
        case 2:
            ShowFuture();
            break;
    }
    
}

void ShowSelection()
{
    DrawLine((SCREEN_WIDTH/2), 0, (SCREEN_WIDTH/2), SCREEN_HEIGHT, WHITE);
    
    Rectangle pastRect = {0, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT};
    Rectangle futureRect = {SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT};
    
    if(CheckCollisionPointRec(GetMousePosition(), pastRect))
    {
        DrawRectangleGradientV(
            0, 
            0, 
            SCREEN_WIDTH/2, 
            SCREEN_HEIGHT, 
            Fade(WHITE, 0.0), 
            Fade(WHITE, 0.5)
        );
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            selectedRole = 1;
        }
        
    }
    
    if(CheckCollisionPointRec(GetMousePosition(), futureRect))
    {
        DrawRectangleGradientV(
            SCREEN_WIDTH/2, 
            0, 
            SCREEN_WIDTH/2, 
            SCREEN_HEIGHT, 
            Fade(WHITE, 0.0), 
            Fade(WHITE, 0.5)
        );
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            selectedRole = 2;
        }
        
    }
    
    DrawText("PAST", SCREEN_WIDTH/4 - (pastTextWidth/2), (SCREEN_HEIGHT/2)-20, 40, WHITE);
    DrawText("FUTURE", SCREEN_WIDTH*3/4 - (pastTextWidth/2), (SCREEN_HEIGHT/2)-20, 40, WHITE);
}

void ShowPast()
{
    Rectangle line = {SCREEN_WIDTH*2/3, 0, SCREEN_WIDTH/3, SCREEN_HEIGHT};

    DrawRectangleGradientH(
        line.x,
        line.y,
        line.width,
        line.height,
        Fade(WHITE, 0.0),
        Fade(WHITE, 0.5)
    );
    
    DrawText("PAST", 70, 100, 70, WHITE);
    DrawText("lorem ipsum dolor", 70, 200, 30, WHITE);
    DrawText("lorem ipsum dolor", 70, 240, 30, WHITE);
    
    // BUTTON
    Rectangle button = {70, 300, MeasureText("Start new game", 20) + 20, 40};               
    buttonClicked = UIButton(button, "Start new game", DARKGRAY);
    if (buttonClicked)
    {
        game.role = ROLE_PAST;
        UnloadRoleScene();
    }
}

void ShowFuture()
{
    Rectangle line = {0, 0, SCREEN_WIDTH/3, SCREEN_HEIGHT};
    
    DrawRectangleGradientH(
        line.x,
        line.y,
        line.width,
        line.height,
        Fade(WHITE, 0.5),
        Fade(WHITE, 0.0)
    );
    
    DrawText("FUTURE", SCREEN_WIDTH-MeasureText("FUTURE", 70)-70, 100, 70, WHITE);
    // BUTTON
    Rectangle button = {SCREEN_WIDTH-MeasureText("Start new game", 20)-90, 300, MeasureText("Start new game", 20) + 20, 40};               
    buttonClicked = UIButton(button, "Start new game", DARKGRAY);
    if (buttonClicked)
    {
        game.role = ROLE_FUTURE;
        UnloadRoleScene();
    }
}



void UnloadRoleScene()
{
    ChangeScene(SCENE_INTRO);
}