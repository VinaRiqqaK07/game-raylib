#include "raylib.h"
#include <stddef.h>
#include "utils/constants.h"
#include "core/game.h"
#include "core/scene_manager.h"

// Program main entry point
int main(void)
{
    // Initialization
    const int screenWidth = SCREEN_WIDTH;
    const int screenHeight = SCREEN_HEIGHT;
    
    GameScene lastScene = -1;
    
    Music *currentMusic = NULL;
    

    InitWindow(screenWidth, screenHeight, "Between Two Moments");
    
    InitAudioDevice();
    
    Music ending = LoadMusicStream("../assets/music/ending.mp3");
    Music puzzle = LoadMusicStream("../assets/music/Game.mp3");
    Music intro = LoadMusicStream("../assets/music/Intro.mp3");
    
    //SetMusicLooping(intro, true);
    //SetMusicLooping(puzzle, true);
    //SetMusicLooping(ending, true);

    SetTargetFPS(60);      // Set our game to run at 60 frames-per-second
    
    InitGameState();
    ChangeScene(SCENE_MENU);
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        // Update variables
        UpdateScene();
        
        
        // ======= MUSIC MANAGER ============
        GameScene scene = GetCurrentScene();
        
        
        if (scene != lastScene)
        {
            /*
            if (currentMusic != NULL)
            {
                StopMusicStream(*currentMusic);
            }*/

            // tentukan music baru
            switch(scene)
            {
                case SCENE_MENU:
                    currentMusic = NULL;
                    break;
                    
                case SELECT_ROLE:
                    currentMusic = NULL;
                    break;
                    
                case SCENE_INTRO:
                    currentMusic = &intro;
                    break;

                case SCENE_PUZZLE1:
                    StopMusicStream(*currentMusic);
                    currentMusic = &puzzle;
                    break;
                    
                case SCENE_PUZZLE2:
                    currentMusic = &puzzle;
                    break;
                    
                case SCENE_PUZZLE3:
                    currentMusic = &puzzle;
                    break;
                    
                case SCENE_PUZZLE4:
                    currentMusic = &puzzle;
                    break;
                    
                case SCENE_ENDING:
                    StopMusicStream(*currentMusic);
                    currentMusic = &ending;
                    break;
            }

            // play music baru
            if (currentMusic != NULL)
            {
                PlayMusicStream(*currentMusic);
            }

            lastScene = scene;
        }
    
        
        if (currentMusic != NULL)
            UpdateMusicStream(*currentMusic);
    
        // Draw
        BeginDrawing();
        
            DrawScene();
            
        EndDrawing();
        //----------------------------------------------------------------------------------
        
    }

    // De-Initialization
    UnloadMusicStream(*currentMusic);
    CloseAudioDevice();
    
    CloseWindow();        // Close window and OpenGL context

    return 0;
}
