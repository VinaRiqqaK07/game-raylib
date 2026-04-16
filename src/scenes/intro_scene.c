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
#include <math.h>
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
Font monologFont;

void InitIntroScene()
{
    monologFont = LoadFont("../assets/font/Margon-360-Bold.otf");
    
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
    
    captions[0] = "Once, there was a happy family, holding onto a quite moment that felt like it would last forever.";
    captions[1] = "They left for what should've been just another normal drive.";
    captions[2] = "Nothing felt wrong-just an ordinary day, like any other.";
    captions[3] = "Then, everything changed-headlights, no time to react.";
    captions[4] = "One survived. One didn't.";
    captions[5] = "Years later, only one remains, stuck in a memory they can't let go.";
    captions[6] = "The father starts building time machine to go back.";
    captions[7] = "He spends years trying to make it work.";
    captions[8] = "He almost gives up.";
    captions[9] = "Then it finally works-the past appears again.";
    captions[10] = "The moment before everything went wrong is within reach";
    captions[11] = "He steps forward, knowing he can't fix it alone-he has to face it together across time.";
    
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
    DrawRectangle(
        0,
        SCREEN_HEIGHT - 150,
        SCREEN_WIDTH,
        150,
        Fade(BLACK, 0.6f * alpha)
    );
    
    int fontSize = 23;
    int spacing = 2;
    //int textWidth = MeasureText(captions[currentIntro], fontSize);
    Vector2 size = MeasureTextEx(monologFont, captions[currentIntro], fontSize, spacing);
    Color outerGlow = (Color){255, 220, 120, 255};

    //GLOW TEXT
    Vector2 pos = {SCREEN_WIDTH/2 - size.x/2, SCREEN_HEIGHT - 80};

    // OUTER GLOW TIPIS (radius 1)
    for (int i = -2; i <= 2; i++)
    {
        for (int j = -2; j <= 2; j++)
        {
            // skip tengah (biar ini pure outer glow)
            if (i == 0 && j == 0) continue;

            float dist = sqrtf(i*i + j*j); // 1 atau 1.4 (diagonal)
            float alphaGlow = 0.18f * (1.0f - dist / 1.5f);

            DrawTextEx(
                monologFont,
                captions[currentIntro],
                (Vector2){pos.x + i, pos.y + j},
                fontSize,
                spacing,
                Fade(outerGlow, 0.1f)
            );
        }
    }

    // MAIN TEXT
    DrawTextEx(monologFont, captions[currentIntro], pos, fontSize, spacing, Fade(WHITE, alpha));
}

void UnloadIntroScene()
{
    for (int i = 0; i < TOTAL_INTRO; i++)
    {
        UnloadTexture(introImages[i]);
    }
}