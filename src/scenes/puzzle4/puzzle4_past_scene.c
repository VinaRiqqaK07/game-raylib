#include "raylib.h"
#include "../../utils/constants.h"
#include "../../core/game.h"
#include "../../core/scene_manager.h"
#include "../../systems/lighting_system.h"
#include "../../systems/moments_system.h"

Texture bgPuzzle4, albumTextureP4, photo1AlbumP4, photo2AlbumP4, photo3AlbumP4, photo4AlbumP4;
Rectangle sourceAlbumP4;
Rectangle destAlbumP4;

bool albumPast4Open = false;
//LightingSystem lightSys;

LightSystem light;
WallSystem walls;

Rectangle wall1 = {255, 18, 503, 35};
Rectangle wall2 = {255, 217, 355, 30};
Rectangle wall3 = {255, 418, 263, 23};
Rectangle wall4 = {255, 300, 65, 360};
Rectangle wall5 = {733, 17, 30, 250};
Rectangle wall6 = {680, 217, 290, 30};
Rectangle wall7 = {730, 320, 30, 100};
Rectangle wall8 = {598, 416, 25, 242};
Rectangle wall9 = {690, 418, 250, 25};
Rectangle wall10 = {915, 217, 150, 440};
Rectangle wall11 = {255, 613, 715, 150};
Rectangle wall12 = {578, 416, 65, 25};
Rectangle wall13 = {255, 18, 50, 45};
Rectangle wall14 = {255, 196, 30, 53};

Rectangle checkPoint1 = {320, 65, 50, 50};
Rectangle checkPoint2 = {680, 490, 150, 150};
bool point1Visited = false;
bool point2Visited = false;    
bool triggerAlbumOnce = false;

void InitPuzzle4PastScene()
{
    bgPuzzle4 = LoadTexture("../assets/puzzle4/past/background_puzzle4_past.png");
    
    albumTextureP4 = LoadTexture("../assets/room0/artboard-album_room0_past.png");
    photo1AlbumP4 = LoadTexture("../assets/room0/photo1-album_room0_past.png");
    photo2AlbumP4 = LoadTexture("../assets/puzzle2/photo2_puzzle2_past.png");
    photo3AlbumP4 = LoadTexture("../assets/puzzle3/past/photo3_puzzle3_past.png");
    photo4AlbumP4 = LoadTexture("../assets/puzzle4/past/pic4_puzzle4_past.png");
    
    sourceAlbumP4 = (Rectangle){0, 0, albumTextureP4.width, albumTextureP4.height};
    destAlbumP4 = (Rectangle){SCREEN_WIDTH - 160, SCREEN_HEIGHT - 160, 120, 120};
    
    InitLighting(&light, 100, 300, 130);
    InitWalls(&walls);

    // add wall dari asset kamu
    AddWall(&walls, wall1);
    AddWall(&walls, wall2);
    AddWall(&walls, wall3);
    AddWall(&walls, wall4);
    AddWall(&walls, wall5);
    AddWall(&walls, wall6);
    AddWall(&walls, wall7);
    AddWall(&walls, wall8);
    AddWall(&walls, wall9);
    AddWall(&walls, wall10);
    AddWall(&walls, wall11);
    AddWall(&walls, wall12);
    AddWall(&walls, wall13);
    AddWall(&walls, wall14);
}

void UpdatePuzzle4PastScene()
{
    if(!albumPast4Open && !CheckCollisionPointRec(GetMousePosition(), destAlbumP4))
    {
        UpdateLighting(&light, &walls);
    }
    
    if (CheckCollisionCircleRec(light.position, light.radius - 150, checkPoint1))
    {
        point1Visited = true;
    }
    
    if (CheckCollisionCircleRec(light.position, light.radius, checkPoint2))
    {
        point2Visited = true;
        
        
    }
    
    if (point1Visited && point2Visited && !triggerAlbumOnce)
    {
        triggerAlbumOnce = true;
        destAlbumP4 = (Rectangle){SCREEN_WIDTH/2 - 250, SCREEN_HEIGHT/2 - 250, 500, 500};
        albumPast4Open = true;
    }
    
    if (point1Visited && point2Visited && !albumPast4Open && triggerAlbumOnce)
    {
        UpdateMoments();
    }
    
    
    
    
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();
        
        if(!albumPast4Open && CheckCollisionPointRec(GetMousePosition(), destAlbumP4))
        {
            destAlbumP4 = (Rectangle){SCREEN_WIDTH/2 - 250, SCREEN_HEIGHT/2 - 250, 500, 500};
            albumPast4Open = true;
        }
        else if(albumPast4Open && !CheckCollisionPointRec(GetMousePosition(), destAlbumP4))
        {
            destAlbumP4 = (Rectangle){SCREEN_WIDTH - 150, SCREEN_HEIGHT - 150, 100, 100};
            albumPast4Open = false;
        }
    }
}

void DrawPuzzle4PastScene()
{
    ClearBackground(BLACK);
    
    DrawTexturePro(bgPuzzle4, (Rectangle){0, 0, bgPuzzle4.width, bgPuzzle4.height}, (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, (Vector2){0, 0}, 0.0f, WHITE);
    
    /*
    DrawRectangleRec(checkPoint1, RED);
    DrawRectangleRec(checkPoint2, BLUE);*/
    
    // gambar wall (debug)
    for (int i = 0; i < walls.wallCount; i++)
    {
        DrawRectangleRec(walls.walls[i], DARKGRAY);
    }

    // overlay lighting
    DrawLighting(&light);
    
    if(albumPast4Open)
    {
        DrawRectangle(0, 0, SCREEN_WIDTH,SCREEN_HEIGHT, Fade(BLACK, 0.5f));
            
        DrawTexturePro(albumTextureP4, sourceAlbumP4, destAlbumP4, (Vector2){0, 0}, 0.0f, WHITE);
            
        DrawTexturePro(photo1AlbumP4, (Rectangle){0, 0, photo1AlbumP4.width, photo1AlbumP4.height}, (Rectangle){682, 130, 300, (300 * photo1AlbumP4.height/photo1AlbumP4.width)}, (Vector2){0, 0}, 2.0f, WHITE);
        
        DrawTexturePro(photo3AlbumP4, (Rectangle){0, 0, photo3AlbumP4.width, photo3AlbumP4.height}, (Rectangle){680, 350, 300, (300 * photo3AlbumP4.height/photo3AlbumP4.width)}, (Vector2){0, 0}, -1.0f, WHITE);
            
        DrawTexturePro(photo2AlbumP4, (Rectangle){0, 0, photo2AlbumP4.width, photo2AlbumP4.height}, (Rectangle){285, 55, 320, (320 * photo2AlbumP4.height/photo2AlbumP4.width)}, (Vector2){0, 0}, -1.7f, WHITE);
        
        if (point1Visited && point2Visited)
        {
            DrawTexturePro(photo4AlbumP4, (Rectangle){0, 0, photo4AlbumP4.width, photo4AlbumP4.height}, (Rectangle){270, 300, 320, (320 * photo4AlbumP4.height/photo4AlbumP4.width)}, (Vector2){0, 0}, -1.7f, WHITE);
        }
            
        
        
    }
    else 
    {
        DrawRectangle(destAlbumP4.x - 5, destAlbumP4.y - 5, destAlbumP4.width + 10, destAlbumP4.height + 10, Fade(BLACK, 0.3f));
        DrawTexturePro(albumTextureP4, sourceAlbumP4, destAlbumP4, (Vector2){0, 0}, 0.0f, WHITE);
    }
    
    if (point1Visited && point2Visited && !albumPast4Open && triggerAlbumOnce)
    {
        DrawMoments();
    }
}

void UnloadPuzzle4PastScene()
{
    UnloadTexture(bgPuzzle4);
    UnloadTexture(albumTextureP4);
    UnloadTexture(photo1AlbumP4);
    UnloadTexture(photo2AlbumP4);
    UnloadTexture(photo3AlbumP4);
    UnloadTexture(photo4AlbumP4);
}