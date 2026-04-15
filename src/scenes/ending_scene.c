/**
 * File: ending_scene.c
 * Description:
 * Handles the logic and rendering for Ending Scene before entering gameplay.
 * This room contains pictures assets.
 *
 * Responsibilities:
 * - Initialize textures
 * - Handle caption render 
 *
 *
 *
 */

#include "raylib.h"
#include "ending_scene.h"
#include "../utils/constants.h"
#include "../core/scene_manager.h"
#include "../core/game.h"
#include "../systems/save_system.h"


#define TOTAL_ENDING 4   
#define SHOW_ENDING_TIME 4.0f
#define FADE_ENDING_TIME 1.0f

Texture2D endingImages[TOTAL_ENDING];
const char *endingCaptions[TOTAL_ENDING];

Vector2 spritePositions[TOTAL_ENDING];

float scaleSprite = 0.2f;

int currentEnding = 0;
float endingTimer = 0.0f;
Font fontEnding;

void InitEndingScene()
{
    fontEnding = LoadFont("../assets/font/Margon-360-Bold.otf");
    
    endingImages[0] = LoadTexture("../assets/ending/pic1_ending.png");
    endingImages[1] = LoadTexture("../assets/ending/pic2_ending.png");
    endingImages[2] = LoadTexture("../assets/ending/pic3_ending.png");
    endingImages[3] = LoadTexture("../assets/ending/pic4_ending.png");
    
    if (game.role == ROLE_PAST)
    {
        endingCaptions[1] = "This photo... someone's handing him car keys.\nWhat's about to happen...?";
        endingCaptions[0] = "The clock... It worked. And this photo..\nWhy is only my son circled? \nIs something going to happen to him?";
        endingCaptions[2] = "Another photo... a car this time. Why does this feel... wrong?";
        endingCaptions[3] = "This is all of us... They're smiling...\nI can't change what will happen,\nbut atleast I gave them this moment.";
    }
    else if (game.role == ROLE_FUTURE)
    {
        endingCaptions[1] = "I lost my son in a car accident. I tried to change it-\ngoing back, warning my past self, doing everything";
        endingCaptions[0] = "I could stop him from getting into that car. But no matter what i did, \nthe outcome never changed.";
        endingCaptions[2] = "Fate stayed the same.\nSo maybe the only thing left isn't to fight it anymore, \nbut to accept it.";
        endingCaptions[3] = "To go back not to prevent the inevitable, but to cherish\nwhat little time we had left-to hold onto those final moments, \nand make sure they were seen, felt, and remembered.";
    }

    float startX = 100;
    float y = 100;

    Texture2D placeholder = endingImages[0];

    spritePositions[0] = (Vector2){startX, y};
    spritePositions[1] = (Vector2){
        startX + 700,
        y - 50
    };
    spritePositions[2] = (Vector2){
        startX + 300,
        y + 200
    };
    spritePositions[3] = (Vector2){
        startX + 150,
        y - 100
    };

    currentEnding = 0;
    endingTimer = 0.0f;
}

void UpdateEndingScene()
{
    endingTimer += GetFrameTime();

    if (endingTimer >= SHOW_ENDING_TIME)
    {
        endingTimer = 0.0f;
        currentEnding++;

        if (currentEnding >= TOTAL_ENDING)
        {
            // selesai ending (bisa ke credit / menu)
            DeleteSave();
            ChangeScene(SCENE_MENU);
        }
    }
}

void DrawEndingScene()
{
    ClearBackground(BLACK);

    // draw semua foto yang SUDAH muncul
    for(int i = 0; i <= currentEnding && i < TOTAL_ENDING; i++)
    {
        Texture2D tex = endingImages[i];

        float alpha = 1.0f;

        // hanya foto terakhir yang fade
        if(i == currentEnding)
        {
            if (endingTimer < FADE_ENDING_TIME)
                alpha = endingTimer / FADE_ENDING_TIME;
            else
                alpha = 1.0f;
        }

        float width = tex.width * scaleSprite;
        float height = tex.height * scaleSprite;

        DrawTexturePro(
            tex,
            (Rectangle){0, 0, tex.width, tex.height},
            (Rectangle){
                spritePositions[i].x,
                spritePositions[i].y,
                width,
                height
            },
            (Vector2){0, 0},
            0,
            Fade(WHITE, alpha)
        );
    }

    // ===== CAPTION =====
    if(currentEnding < TOTAL_ENDING)
    {
        int fontSize = 30;
        int textWidth = MeasureText(endingCaptions[currentEnding], fontSize);

        DrawRectangle(
            0,
            SCREEN_HEIGHT - 150,
            SCREEN_WIDTH,
            150,
            Fade(BLACK, 0.6f)
        );

        //DrawText(endingCaptions[currentEnding],SCREEN_WIDTH/2 - textWidth/2,SCREEN_HEIGHT - 120,fontSize,WHITE);
        DrawTextEx(fontEnding, endingCaptions[currentEnding], (Vector2){SCREEN_WIDTH/2 - textWidth/2,SCREEN_HEIGHT - 120}, fontSize, 2, WHITE);
    }
}

void UnloadEndingScene()
{
    
}