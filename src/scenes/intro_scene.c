/**
 * File: intro_scene.c
 * Description:
 * Handles the logic and rendering for Intro Scene before entering gameplay.
 * This room contains background assets (not finished asset yet) with interactable computer area.
 *
 * Responsibilities:
 * - Initialize textures
 * - Handle caption render
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


#define TOTAL_INTRO 12
#define SHOW_TIME 4.0f
#define FADE_TIME 1.0f

Texture2D introImages[TOTAL_INTRO];
const char *captions[TOTAL_INTRO];

int currentIntro = 0;
float introTimer = 0.0f;

Rectangle sourceIntro;
Rectangle destIntro;

int dialogueIndex = 0;

Caption captionIntro;

void InitIntroScene()
{
    introImages[0] = LoadTexture("../assets/intro/image-1.jpg");
    introImages[1] = LoadTexture("../assets/intro/image-2.jpg");
    introImages[2] = LoadTexture("../assets/intro/image-3.jpg");
    introImages[3] = LoadTexture("../assets/intro/image-4.jpg");
    introImages[4] = LoadTexture("../assets/intro/image-5.jpg");
    introImages[5] = LoadTexture("../assets/intro/image-6.jpg");
    introImages[6] = LoadTexture("../assets/intro/image-7.jpg");
    introImages[7] = LoadTexture("../assets/intro/image-8.jpg");
    introImages[8] = LoadTexture("../assets/intro/image-9.jpg");
    introImages[9] = LoadTexture("../assets/intro/image-10.jpg");
    introImages[10] = LoadTexture("../assets/intro/image-11.jpg");
    introImages[11] = LoadTexture("../assets/intro/image-12.jpg");
    
    captions[0] = "We had our perfect now.\nOur future was written in warm light";
    captions[1] = "Just a normal Tuesday.\nA simple drive home";
    captions[2] = "Just a few more minutes.\nJust a simple moment of time";
    captions[3] = "Then, the other moment. The light";
    captions[4] = "The sound. The awful sound.";
    captions[5] = "Now only a broken echo remains.";
    captions[6] = "But a 'broken echo' can still pulsate.\nI knew it, I had to try";
    captions[7] = "With crude tools and falling memory, I spent years.\nWorking to amplify the faint sig...";
    captions[8] = "..nal. The silence was absolute.\nMy own voice, lost in the void.";
    captions[9] = "Then... a tremor. Not just sound, but a pulse.\nA memory.. but external";
    captions[10] = "A path accross the abyss open. But i cannot traverse\nit alone. I need two hands.";
    captions[11] = "To fix the broken moments, we must walk them\ntogether. Your memory.. is our path.";
    
    sourceIntro = (Rectangle){0, 0, introImages[0].width, introImages[0].height};
    destIntro = (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    currentIntro = 0;
    introTimer = 0.0f;
    
    InitCaptionSystem(&captionIntro);
}

void UpdateIntroScene()
{
    introTimer += GetFrameTime();

    if (introTimer >= SHOW_TIME)
    {
        introTimer = 0.0f;
        currentIntro++;

        if (currentIntro >= TOTAL_INTRO)
        {
            game.currentLevel = 1;
            SaveGameFunc();
                
            ChangeScene(SCENE_PUZZLE1);
        }
    }
}

void DrawIntroScene()
{
    ClearBackground(BLACK);

    if (currentIntro >= TOTAL_INTRO) return;

    Texture2D tex = introImages[currentIntro];

    // Hitung alpha fade
    float alpha = 1.0f;

    if (introTimer < FADE_TIME)
    {
        // Fade in
        alpha = introTimer / FADE_TIME;
    }
    else if (introTimer > SHOW_TIME - FADE_TIME)
    {
        // Fade out
        alpha = (SHOW_TIME - introTimer) / FADE_TIME;
    }
    else
    {
        alpha = 1.0f;
    }

    // Draw image fullscreen
    DrawTexturePro(
        tex,
        (Rectangle){0, 0, tex.width, tex.height},
        (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT},
        (Vector2){0, 0},
        0.0f,
        Fade(WHITE, alpha)
    );

    // ===== CAPTION =====
    int fontSize = 30;
    int textWidth = MeasureText(captions[currentIntro], fontSize);

    DrawRectangle(
        0,
        SCREEN_HEIGHT - 150,
        SCREEN_WIDTH,
        150,
        Fade(BLACK, 0.6f * alpha)
    );

    DrawText(
        captions[currentIntro],
        SCREEN_WIDTH/2 - textWidth/2,
        SCREEN_HEIGHT - 130,
        fontSize,
        Fade(WHITE, alpha)
    );
}

void UnloadIntroScene()
{
    for (int i = 0; i < TOTAL_INTRO; i++)
    {
        UnloadTexture(introImages[i]);
    }
}