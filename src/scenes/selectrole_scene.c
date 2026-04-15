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
const char *pastDetail;
const char *futureText;
const char *futureDetail;

bool futureSelectedButton = false;
bool pastSelectedButton = false;

Font descFont;

void InitRoleScene()
{
    descFont = LoadFont("../assets/font/Margon-360-Bold.otf");
    backgroundRole = LoadTexture("../assets/role/background.jpeg");
    selectFutureButton = LoadTexture("../assets/role/select-future.jpeg");
    selectPastButton = LoadTexture("../assets/role/select-past.jpeg");
    
    selectedRole = 0;
    pastText = "PAST";
    pastDetail = "You move through a world \nuntouched by regretwhere every \nchoice feels small and every moment \nslips by unnoticed. Yet faint echoes \nfrom somewhere beyond our time \nbegin to surface, guiding your steps \nin ways you dont fully understand. \nHere, you are possibility-each action \nquietly shaping a future you cannot \nyet see.";
    
    futureText = "FUTURE";
    futureDetail = "You exist in the shadow of what \nhas already been lost,carrying the \nweight of a moment you wish you \ncould take back. Through broken \nfragments of time, you reach into \nthe past-not to command, but to guide, \nto whisper where silence once cost \neverything. Here, you are consequence-\nevery message a fragile chance to \nchange what once seemed inevitable.";
    
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
    
    Rectangle buttonPast = {300, 350, 250, 50};               
    pastSelectedButton = UIButton(buttonPast, selectPastButton);
    
    //DrawText(pastDetail, 250, 420, 15, WHITE);
    DrawTextEx(descFont, pastDetail, (Vector2){240, 420}, 17, 2, WHITE);
    
    Rectangle buttonFuture = {760, 350, 250, 50};               
    futureSelectedButton = UIButton(buttonFuture, selectFutureButton);
    //DrawText(futureDetail, 710, 420, 15, WHITE);
    DrawTextEx(descFont, futureDetail, (Vector2){700, 420}, 17, 2, WHITE);
}


void UnloadRoleScene()
{
    UnloadTexture(backgroundRole);
    UnloadTexture(selectFutureButton);
    UnloadTexture(selectPastButton);
}