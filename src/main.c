#include "raylib.h"
#include "utils/constants.h"
#include "core/game.h"
#include "core/scene_manager.h"

// Program main entry point
int main(void)
{
    // Initialization
    const int screenWidth = SCREEN_WIDTH;
    const int screenHeight = SCREEN_HEIGHT;
    

    InitWindow(screenWidth, screenHeight, "Between Two Moments");

    SetTargetFPS(60);      // Set our game to run at 60 frames-per-second
    
    
    InitGameState();
    ChangeScene(SCENE_MENU);
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update variables
        UpdateScene();
        
        // Draw
        
        BeginDrawing();
        
            DrawScene();
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
  
    CloseWindow();        // Close window and OpenGL context

    return 0;
}
