#include "raylib.h"
#include "intro_scene.h"
#include "../utils/constants.h"
#include "../core/scene_manager.h"
#include "../core/game.h"
#include "../systems/save_system.h"

#define SPRITE_COUNT 4
#define SPAWN_DELAY 10.0f
#define FADE_TIME 3.0f

float timer = 0;
float scaleSprite = 0.1f;
bool introFinish = false;
Texture2D placeholder;
Vector2 spritePositions[SPRITE_COUNT];

void InitIntroScene()
{
    placeholder = LoadTexture("../assets/placeholder.jpg");

    float startX = 100;
    float y = 100;
    
    spritePositions[0] = (Vector2){
        startX,
        y
    };
    spritePositions[1] = (Vector2){
        startX + (placeholder.width * scaleSprite)/1.5,
        y - 20
    };
    spritePositions[2] = (Vector2){
        startX + (placeholder.width * scaleSprite)-100,
        y + (placeholder.height * scaleSprite)
    };
    spritePositions[3] = (Vector2){
        startX + (placeholder.width * scaleSprite * 1.5),
        y + placeholder.height * scaleSprite/1.3
    };

}

void UpdateIntroScene()
{
    timer += GetFrameTime();

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        int currentIndex = timer / SPAWN_DELAY;

        if(currentIndex < SPRITE_COUNT - 1)
        {
            timer = (currentIndex + 1) * SPAWN_DELAY;
        }
    }
    
    if(timer > 30.0f)
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || timer >= 33.0f)
        {
            UnloadIntroScene();
        }
    }
}

void DrawIntroScene()
{
    ClearBackground(BLACK);
    //DrawText("ALBUM", (SCREEN_WIDTH/2)- MeasureText("ALBUM", 70), 50, 70, WHITE);

    for(int i = 0; i < SPRITE_COUNT; i++)
    {
        float spawnTime = i * SPAWN_DELAY;

        if(timer >= spawnTime)
        {
            float timeSinceSpawn = timer - spawnTime;

            float alpha = 1.0f;

            if(timeSinceSpawn < FADE_TIME)
                alpha = timeSinceSpawn / FADE_TIME;

            Color tint = Fade(WHITE, alpha);

            // ROTATION
            float rotation = (i % 2 == 0) ? -10.0f : 10.0f;
            
            //void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint)
            
            DrawTextureEx(placeholder, spritePositions[i], rotation, 0.1f, tint);
        }
        
        
    }
    
    
}

void UnloadIntroScene()
{
    game.currentLevel = 1;
    SaveGameFunc();
    
    ChangeScene(SCENE_PUZZLE1);
}