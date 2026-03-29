/**
 * File: selectrole_scene.c
 * Description:
 * Handles the logic and rendering for Selecting Role.
 * This scene contains two selection of role and description for each role.
 *
 * If role is selected, the game state for role will be updated.
 *
 */

#include "raylib.h"
#include "selectrole_scene.h"
#include "../utils/constants.h"
#include "../core/game.h"
#include "../core/scene_manager.h"
#include "../systems/ui_system.h"

Texture2D backgroundRole, selectFutureButton, selectPastButton;

int selectedRole;
int pastTextWidth;
int futureTextWidth;
const char *pastText;
const char *futureText;

bool futureSelectedButton = false;
bool pastSelectedButton = false;

void InitRoleScene()
{
    backgroundRole = LoadTexture("../assets/role/background.jpeg");
    selectFutureButton = LoadTexture("../assets/role/select-future.jpeg");
    selectPastButton = LoadTexture("../assets/role/select-past.jpeg");
    
    selectedRole = 0;
    pastText = "PAST";
    futureText = "FUTURE";
    
    pastTextWidth = MeasureText(pastText, 40);
    futureTextWidth = MeasureText(futureText, 40);
    
}

void UpdateRoleScene()
{
    if (pastSelectedButton)
    {
        game.role = ROLE_PAST;
        ChangeScene(SCENE_INTRO);
    }
    else if (futureSelectedButton)
    {
        game.role = ROLE_FUTURE;
        ChangeScene(SCENE_INTRO);
    }
}

void DrawRoleScene()
{
    ClearBackground(BLACK);
    
    DrawTexturePro(backgroundRole, (Rectangle){0, 0, backgroundRole.width, backgroundRole.height}, (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, (Vector2){0, 0}, 0.0f, WHITE);
    
    Rectangle buttonPast = {300, 400, 250, 50};               
    pastSelectedButton = UIButton(buttonPast, selectPastButton);
    
    Rectangle buttonFuture = {760, 400, 250, 50};               
    futureSelectedButton = UIButton(buttonFuture, selectFutureButton);
}


void UnloadRoleScene()
{
    UnloadTexture(backgroundRole);
    UnloadTexture(selectFutureButton);
    UnloadTexture(selectPastButton);
}