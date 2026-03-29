/**
 * File: puzzle4_past_scene.c
 * Description:
 * Handles the logic and rendering for Puzzle 4 PAST role Scene.
 * This room contains pictures assets, sequence puzzle, shadow environment, draggable light
 * and input field.
 *
 * Responsibilities:
 * - Initialize textures.
 * - Handle assets and shadow render, sequence puzzle, and draggable light.
 *
 *
 *
 */
 
#include "raylib.h"
#include <stdio.h>
#include "../../utils/constants.h"
#include "../../core/game.h"
#include "../../core/scene_manager.h"
#include "../../systems/lighting_system.h"
#include "../../systems/moments_system.h"
#include "../../systems/sequence_system.h"

// ========== INITIALIZATION ==================
Texture bgPuzzle4, albumTextureP4, photo1AlbumP4, photo2AlbumP4, photo3AlbumP4, photo4AlbumP4;
Rectangle sourceAlbumP4;
Rectangle destAlbumP4;

bool albumPast4Open = false;

// ============ INITIALIZE LIGHT SYSTEM & WALLS ==========
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

// ============= INITIALIZE AREA MAP CHECKPOINT ==========
Rectangle checkPoint1 = {320, 65, 50, 50};
Rectangle checkPoint2 = {680, 490, 150, 150};
bool point1Visited = false;
bool point2Visited = false;    
bool triggerAlbumOnce = false;

// ============== INITIALIZE SEQUENCE PUZZLE =======
Rectangle symbol1P4 = {500, 340, 30, 30};
Rectangle symbol2P4 = {485, 370, 30, 30};
Rectangle symbol3P4 = {470, 400, 30, 30};
Rectangle symbol4P4Past = {460, 430, 33, 35};
bool IsPhoto4Shown = false;

SymbolPuzzle symbolSequenceP4Past;

void InitPuzzle4PastScene()
{
    // ============ LOAD TEXTURE ==============
    bgPuzzle4 = LoadTexture("../assets/puzzle4/past/background_puzzle4_past.png");
    
    albumTextureP4 = LoadTexture("../assets/room0/artboard-album_room0_past.png");
    photo1AlbumP4 = LoadTexture("../assets/room0/photo1-album_room0_past.png");
    photo2AlbumP4 = LoadTexture("../assets/puzzle2/photo2_puzzle2_past.png");
    photo3AlbumP4 = LoadTexture("../assets/puzzle3/past/photo3_puzzle3_past.png");
    photo4AlbumP4 = LoadTexture("../assets/puzzle4/past/pic4_puzzle4_past.png");
    
    sourceAlbumP4 = (Rectangle){0, 0, albumTextureP4.width, albumTextureP4.height};
    destAlbumP4 = (Rectangle){SCREEN_WIDTH - 160, SCREEN_HEIGHT - 160, 120, 120};
    
    // =============== LIGHT SYSTEM =============
    InitLighting(&light, 100, 300, 130);
    InitWalls(&walls);

    // Add walls referencing the assets.
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
    
    // ======== SEQUENCING PUZZLE ============
    symbolSequenceP4Past.sequence[0] = 2;
    symbolSequenceP4Past.sequence[1] = 1;
    symbolSequenceP4Past.sequence[2] = 4;
    symbolSequenceP4Past.sequence[3] = 3;
    symbolSequenceP4Past.sequence[4] = 4;
    symbolSequenceP4Past.sequence[5] = 2;
    
    symbolSequenceP4Past.sequenceLength = 6;
    
    InitSequencePuzzle(&symbolSequenceP4Past, 6);
    
    InitMoments();
}

void UpdatePuzzle4PastScene()
{
    // ================ HANDLE LIGHTING =============
    if(!albumPast4Open && !CheckCollisionPointRec(GetMousePosition(), destAlbumP4)) //&& (!point1Visited || !point2Visited))
    {
        UpdateLighting(&light, &walls);
    }
    
    // ============= HANDLE AREA CHECKPOINT ============
    if (CheckCollisionCircleRec(light.position, 8.0f, checkPoint1))
    {
        point1Visited = true;
    }
    
    if (CheckCollisionCircleRec(light.position, 8.0f, checkPoint2))
    {
        point2Visited = true;
        
        
    }
    
    if (point1Visited && point2Visited && !triggerAlbumOnce)
    {
        triggerAlbumOnce = true;
        destAlbumP4 = (Rectangle){SCREEN_WIDTH/2 - 250, SCREEN_HEIGHT/2 - 250, 500, 500};
        albumPast4Open = true;
    }
    
    // ============== HANDLE INPUT FIELD ===========
    if (point1Visited && point2Visited && !albumPast4Open && triggerAlbumOnce)
    {
        UpdateMoments();
    }
    
    
    
    // ============== HANDLE ALBUM ACCESS =============
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && point1Visited && point2Visited)
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
        
        if (albumPast4Open)
        {
            if (CheckCollisionPointRec(mouse, symbol1P4))
            {
                AddInput(&symbolSequenceP4Past, 1);
            }
            else if (CheckCollisionPointRec(mouse, symbol2P4))
            {
                AddInput(&symbolSequenceP4Past, 2);
            }
            else if (CheckCollisionPointRec(mouse, symbol3P4))
            {
                AddInput(&symbolSequenceP4Past, 3);
            }
            else if (CheckCollisionPointRec(mouse, symbol4P4Past))
            {
                AddInput(&symbolSequenceP4Past, 4);
            }
        }
    }
    
    // ========== HANDLE SEQUENCE ALBUM PUZZLE ========
    if (albumPast4Open && point1Visited && point2Visited && !symbolSequenceP4Past.solved)
    {
        UpdateSequencePuzzle(&symbolSequenceP4Past);
    }
    else if (albumPast4Open && symbolSequenceP4Past.solved && !IsPhoto4Shown)
    {
        IsPhoto4Shown = true;
    }
}

void DrawPuzzle4PastScene()
{
    ClearBackground(BLACK);
    
    DrawTexturePro(bgPuzzle4, (Rectangle){0, 0, bgPuzzle4.width, bgPuzzle4.height}, (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, (Vector2){0, 0}, 0.0f, WHITE);
    
    // Draw wall
    for (int i = 0; i < walls.wallCount; i++)
    {
        DrawRectangleRec(walls.walls[i], DARKGRAY);
    }

    // overlay lighting
    DrawLighting(&light);
    
    // Draw album
    if(albumPast4Open && point1Visited && point2Visited)
    {
        DrawRectangle(0, 0, SCREEN_WIDTH,SCREEN_HEIGHT, Fade(BLACK, 0.5f));
            
        DrawTexturePro(albumTextureP4, sourceAlbumP4, destAlbumP4, (Vector2){0, 0}, 0.0f, WHITE);
            
        DrawTexturePro(photo1AlbumP4, (Rectangle){0, 0, photo1AlbumP4.width, photo1AlbumP4.height}, (Rectangle){682, 130, 300, (300 * photo1AlbumP4.height/photo1AlbumP4.width)}, (Vector2){0, 0}, 2.0f, WHITE);
        
        DrawTexturePro(photo3AlbumP4, (Rectangle){0, 0, photo3AlbumP4.width, photo3AlbumP4.height}, (Rectangle){680, 350, 300, (300 * photo3AlbumP4.height/photo3AlbumP4.width)}, (Vector2){0, 0}, -1.0f, WHITE);
            
        DrawTexturePro(photo2AlbumP4, (Rectangle){0, 0, photo2AlbumP4.width, photo2AlbumP4.height}, (Rectangle){285, 55, 320, (320 * photo2AlbumP4.height/photo2AlbumP4.width)}, (Vector2){0, 0}, -1.7f, WHITE);
        
        if (point1Visited && point2Visited && IsPhoto4Shown)
        {
            DrawTexturePro(photo4AlbumP4, (Rectangle){0, 0, photo4AlbumP4.width, photo4AlbumP4.height}, (Rectangle){270, 300, 320, (320 * photo4AlbumP4.height/photo4AlbumP4.width)}, (Vector2){0, 0}, -1.7f, WHITE);
        }
        
    }
    else if (point1Visited && point2Visited)
    {
        DrawRectangle(destAlbumP4.x - 5, destAlbumP4.y - 5, destAlbumP4.width + 10, destAlbumP4.height + 10, Fade(BLACK, 0.3f));
        DrawTexturePro(albumTextureP4, sourceAlbumP4, destAlbumP4, (Vector2){0, 0}, 0.0f, WHITE);
    }
    
    // Draw Input Field
    if (point1Visited && point2Visited && !albumPast4Open && triggerAlbumOnce && IsPhoto4Shown)
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