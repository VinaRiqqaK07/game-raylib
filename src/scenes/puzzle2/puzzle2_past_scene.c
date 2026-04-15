/**
 * File: puzzle2_past_scene.c
 * Description:
 * Handles the logic and rendering for Puzzle 2 PAST Scene.
 * This room contains pictures assets, zoom system, and wiring minigame.
 *
 * Responsibilities:
 * - Initialize textures.
 * - Handle zoom system, sequence symbol puzzle, and wiring minigame.
 *
 *
 *
 */
 
#include "raylib.h"
#include <stdio.h>
#include "../../utils/constants.h"
#include "../../core/game.h"
#include "../../core/scene_manager.h"
#include "../../systems/ui_system.h"
#include "../../systems/zoom_system.h"
#include "../../systems/sequence_system.h"
#include "../../systems/caption_system.h"
#include "../../systems/wiring_minigame.h"
#include "../../systems/save_system.h"

Texture2D bgPuzzle2Past, wiringDetail, wiringGame, bwbuttonDetail, albumTextureP2, photo1AlbumP2, photo2AlbumP2;
Rectangle sourceAlbumP2;
Rectangle destAlbumP2;


ZoomSystem zoomPastP2;
WiringSystem wireMinigamePast;
SymbolPuzzle bwSequenceP2Past;
SymbolPuzzle symbolSequenceP2Past;

Rectangle wiringArea = {940, 260, 50, 80};
Rectangle bwButtonArea = {490, 500, 30, 50};
Rectangle blackButtonArea = {590, 260, 130, 130};
Rectangle whiteButtonArea = {590, 395, 130, 130};

Rectangle symbol1P2 = {445, 220, 35, 40};
Rectangle symbol2P2 = {480, 205, 35, 40};
Rectangle symbol3P2 = {515, 190, 35, 40};

bool wireMinigameOpen = false;
bool bwButtonDetailOpen = false;
bool albumPastPuzzle2Open = false;
bool loadnewBWDetail = false;
bool IsPuzzle2PastComplete = false;

void InitPuzzle2PastScene()
{
    wireMinigameOpen = false;
    bwButtonDetailOpen = false;
    albumPastPuzzle2Open = false;
    loadnewBWDetail = false;
    IsPuzzle2PastComplete = false;

    bgPuzzle2Past = LoadTexture("../assets/puzzle2/mainhall_puzzle2_past.jpg");
    wiringDetail = LoadTexture("../assets/puzzle2/wiring-detail_puzzle2_past.jpg");
    wiringGame = LoadTexture("../assets/puzzle2/wiring-game_puzzle2_past.jpg");
    
    bwbuttonDetail = LoadTexture("../assets/puzzle2/bw-button_puzzle2_past.png");
    
    albumTextureP2 = LoadTexture("../assets/room0/artboard-album_room0_past.png");
    photo1AlbumP2 = LoadTexture("../assets/room0/photo1-album_room0_past.png");
    photo2AlbumP2 = LoadTexture("../assets/puzzle2/photo2_puzzle2_past.png");
    
    sourceAlbumP2 = (Rectangle){0, 0, albumTextureP2.width, albumTextureP2.height};
    destAlbumP2 = (Rectangle){SCREEN_WIDTH - 160, SCREEN_HEIGHT - 160, 120, 120};
    
    InitZoomSystem(&zoomPastP2, bgPuzzle2Past);
    
    InitWiring(&wireMinigamePast);
    
    bwSequenceP2Past.sequence[0] = 1;
    bwSequenceP2Past.sequence[1] = 2;
    bwSequenceP2Past.sequence[2] = 2;
    bwSequenceP2Past.sequence[3] = 1;
    bwSequenceP2Past.sequence[4] = 1;
    bwSequenceP2Past.sequence[5] = 2;
    
    bwSequenceP2Past.sequenceLength = 6;
    
    InitSequencePuzzle(&bwSequenceP2Past, 6);
    
    InitWiring(&wireMinigamePast);
    
    symbolSequenceP2Past.sequence[0] = 2;
    symbolSequenceP2Past.sequence[1] = 1;
    symbolSequenceP2Past.sequence[2] = 1;
    symbolSequenceP2Past.sequence[3] = 3;
    symbolSequenceP2Past.sequence[4] = 1;
    symbolSequenceP2Past.sequence[5] = 2;
    
    symbolSequenceP2Past.sequenceLength = 6;
    
    InitSequencePuzzle(&symbolSequenceP2Past, 6);
}

void UpdatePuzzle2PastScene()
{
    if (zoomPastP2.state == ZOOM_IDLE)
    {
        wireMinigameOpen = false;
        bwButtonDetailOpen = false;
    }
    
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();
        
        if(CheckCollisionPointRec(mouse, wiringArea)&& zoomPastP2.state == ZOOM_IDLE && !wireMinigamePast.completed)
        {
            TriggerZoom(&zoomPastP2, wiringDetail);
            wireMinigameOpen = true;
        }
        else if(CheckCollisionPointRec(mouse, bwButtonArea)&& zoomPastP2.state == ZOOM_IDLE && wireMinigamePast.completed)
        {
            TriggerZoom(&zoomPastP2, bwbuttonDetail);
            bwButtonDetailOpen = true;
        }
        
        if (bwButtonDetailOpen)
        {
            if(CheckCollisionPointRec(mouse, blackButtonArea)&& !bwSequenceP2Past.solved)
            {
                AddInput(&bwSequenceP2Past, 1);
            }
            else if(CheckCollisionPointRec(mouse, whiteButtonArea)&& !bwSequenceP2Past.solved)
            {
                AddInput(&bwSequenceP2Past, 2);
            }
        }
        
        if(!albumPastPuzzle2Open && CheckCollisionPointRec(GetMousePosition(), destAlbumP2) && zoomPastP2.state == ZOOM_IDLE)
        {
            destAlbumP2 = (Rectangle){SCREEN_WIDTH/2 - 250, SCREEN_HEIGHT/2 - 250, 500, 500};
            albumPastPuzzle2Open = true;
        }
        else if(albumPastPuzzle2Open && !CheckCollisionPointRec(GetMousePosition(), destAlbumP2) && zoomPastP2.state == ZOOM_IDLE)
        {
            destAlbumP2 = (Rectangle){SCREEN_WIDTH - 150, SCREEN_HEIGHT - 150, 100, 100};
            albumPastPuzzle2Open = false;
        }
        
        if (albumPastPuzzle2Open && !IsPuzzle2PastComplete)
        {
            
            if (CheckCollisionPointRec(GetMousePosition(), symbol1P2))
            {
                AddInput(&symbolSequenceP2Past, 1);
            }
            else if (CheckCollisionPointRec(GetMousePosition(), symbol2P2))
            {
                AddInput(&symbolSequenceP2Past, 2);
            }
            else if (CheckCollisionPointRec(GetMousePosition(), symbol3P2))
            {
                AddInput(&symbolSequenceP2Past, 3);
            }
        }
    }
    
    if (wireMinigameOpen && !wireMinigamePast.completed)
    {
        UpdateWiring(&wireMinigamePast);
        
        if (wireMinigamePast.completed)
        {
            bgPuzzle2Past = LoadTexture("../assets/puzzle2/mainhall-2_puzzle2_past.jpg");
            InitZoomSystem(&zoomPastP2, bgPuzzle2Past);
        }
    }
    
    if (bwButtonDetailOpen && !bwSequenceP2Past.solved)
    {
        UpdateSequencePuzzle(&bwSequenceP2Past);
    }
    else if (bwButtonDetailOpen && bwSequenceP2Past.solved && !loadnewBWDetail)
    {
        bwbuttonDetail = LoadTexture("../assets/puzzle2/bw-results_puzzle2_past.png");
        InitZoomSystem(&zoomPastP2, bgPuzzle2Past);
        loadnewBWDetail = true;
    }
    
    if (albumPastPuzzle2Open && !IsPuzzle2PastComplete)
    {
        UpdateSequencePuzzle(&symbolSequenceP2Past);
        IsPuzzle2PastComplete = symbolSequenceP2Past.solved;
    }
    else if (symbolSequenceP2Past.solved && !IsPuzzle2PastComplete)
    {
        IsPuzzle2PastComplete = true;
    }
    
    UpdateZoomSystem(&zoomPastP2);
    
    if (symbolSequenceP2Past.solved && !albumPastPuzzle2Open)
    {
        game.currentLevel = 3;
        SaveGameFunc();
        
        ChangeScene(SCENE_PUZZLE3);
    }        
}

void DrawPuzzle2PastScene()
{
    //DrawTexturePro(introRoomPast,sourceRoomPast,destRoomPast,(Vector2){0,0},0.0f,WHITE);
    //DrawText("PAST ROOM 0", 200, 150, 20, WHITE);
    
    DrawZoomSystem(&zoomPastP2);
    //DrawText("PAST PUZZLE 2", 200, 150, 20, WHITE);
    
    if (wireMinigameOpen && !wireMinigamePast.completed && zoomPastP2.state == ZOOMED)
    {
        DrawTextureEx(wiringGame, (Vector2){380, 120}, 0.0f, 0.4f, WHITE);
        DrawWiring(&wireMinigamePast);
        
    }
    
    
    
    if(zoomPastP2.state == ZOOM_IDLE)
    {
        if(albumPastPuzzle2Open)
        {
            DrawRectangle(0, 0, SCREEN_WIDTH,SCREEN_HEIGHT, Fade(BLACK, 0.5f));
            
            DrawTexturePro(albumTextureP2, sourceAlbumP2, destAlbumP2, (Vector2){0, 0}, 0.0f, WHITE);
            
            DrawTexturePro(photo1AlbumP2, (Rectangle){0, 0, photo1AlbumP2.width, photo1AlbumP2.height}, (Rectangle){682, 130, 300, (300 * photo1AlbumP2.height/photo1AlbumP2.width)}, (Vector2){0, 0}, 2.0f, WHITE);
            
            if (IsPuzzle2PastComplete)
            {
                DrawTexturePro(photo2AlbumP2, (Rectangle){0, 0, photo2AlbumP2.width, photo2AlbumP2.height}, (Rectangle){285, 55, 320, (320 * photo2AlbumP2.height/photo2AlbumP2.width)}, (Vector2){0, 0}, -1.7f, WHITE);
            }
        }
        else 
        {
            DrawRectangle(destAlbumP2.x - 5, destAlbumP2.y - 5, destAlbumP2.width + 10, destAlbumP2.height + 10, Fade(BLACK, 0.3f));
            DrawTexturePro(albumTextureP2, sourceAlbumP2, destAlbumP2, (Vector2){0, 0}, 0.0f, WHITE);
        }
        
    }
    /*
    if (albumPastPuzzle2Open)
    {
        DrawRectangleRec(symbol1P2, WHITE);
        DrawRectangleRec(symbol2P2, RED);
        DrawRectangleRec(symbol3P2, BLUE);
    }*/
    
    //DrawRectangleRec(bwButtonArea, WHITE);
    
    
    //DrawWiring(&wireMinigamePast);
    //DrawRectangleRec(wiringArea, WHITE);
    //DrawText(TextFormat("inputLength: %d", symbolSequenceP2Past.inputLength), 100, 200, 20, RED);
}

void UnloadPuzzle2PastScene()
{
    UnloadTexture(bgPuzzle2Past);
}