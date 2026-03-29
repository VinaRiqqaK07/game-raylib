/**
 * File: puzzle1_past_scene.c
 * Description:
 * Handles the logic and rendering for Puzzle 1 PAST role Scene.
 * This room contains pictures assets, zoom system, and sequence puzzle systems
 *
 * Responsibilities:
 * - Initialize textures.
 * - Handle zoom system, sequence symbol puzzle, and caption system.
 *
 *
 *
 */

#include "raylib.h"
#include <stdio.h>
#include "puzzle1_past_scene.h"
#include "../../utils/constants.h"
#include "../../core/game.h"
#include "../../core/scene_manager.h"
#include "../../systems/ui_system.h"
#include "../../systems/save_system.h"
#include "../../systems/zoom_system.h"
#include "../../systems/sequence_system.h"
#include "../../systems/caption_system.h"

Texture2D bgPastP1, candleZoom, roundpicZoom, telephoneZoom, albumTexture, photo1Album;
Rectangle sourceRoomPast;
Rectangle destRoomPast;
Rectangle sourceAlbum;
Rectangle destAlbum;

Rectangle zoomCandle = {450, 250, 100, 100};
Rectangle roundPic = {30, 178, 120, 260};
Rectangle telephone = {770, 450, 90, 90};

bool albumPastOpen = false;
ZoomSystem zoom;

SymbolPuzzle symbolSequenceP1;
bool IsPuzzle1PastComplete = false;

Caption captionPast;
bool captionPuzzle1PastFinish = false;
float timerCaption = 0.0f;
int captionPastIndex = 0;

void InitPuzzle1PastScene()
{
    InitCaptionSystem(&captionPast);
    
    bgPastP1 = LoadTexture("../assets/puzzle1/mainhall_puzzle1_past.jpg");
    InitZoomSystem(&zoom, bgPastP1);
    
    candleZoom = LoadTexture("../assets/puzzle1/candle_puzzle1_past.jpg");
    roundpicZoom = LoadTexture("../assets/puzzle1/roundpic_puzzle1_past.png");
    telephoneZoom = LoadTexture("../assets/puzzle1/telephone_puzzle1_past.png");
    
    
    albumTexture = LoadTexture("../assets/room0/artboard-album_room0_past.png");
    photo1Album = LoadTexture("../assets/room0/photo1-album_room0_past.png");
    
    sourceRoomPast = (Rectangle){0, 0, bgPastP1.width, bgPastP1.height};
    destRoomPast = (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    
    sourceAlbum = (Rectangle){0, 0, albumTexture.width, albumTexture.height};
    destAlbum = (Rectangle){SCREEN_WIDTH - 160, SCREEN_HEIGHT - 160, 120, 120};
    
    symbolSequenceP1.sequence[0] = 1;
    symbolSequenceP1.sequence[1] = 2;
    symbolSequenceP1.sequence[2] = 2;
    symbolSequenceP1.sequence[3] = 3;
    symbolSequenceP1.sequence[4] = 1;
    
    symbolSequenceP1.sequenceLength = 5;
    
    InitSequencePuzzle(&symbolSequenceP1, 5);
    //printf("INIT SeqLength: %d\n", symbolSequenceP1.sequenceLength);
}

void UpdatePuzzle1PastScene()
{
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();
        
        if(CheckCollisionPointRec(mouse, zoomCandle)&& zoom.state == ZOOM_IDLE && !albumPastOpen)
        {
            TriggerZoom(&zoom, candleZoom);
        }
        else if(CheckCollisionPointRec(mouse, roundPic)&& zoom.state == ZOOM_IDLE && !albumPastOpen)
        {
            TriggerZoom(&zoom, roundpicZoom);
        }
        else if(CheckCollisionPointRec(mouse, telephone)&& zoom.state == ZOOM_IDLE && !albumPastOpen)
        {
            TriggerZoom(&zoom, telephoneZoom);
        }
        
        if(!albumPastOpen && CheckCollisionPointRec(GetMousePosition(), destAlbum) && zoom.state == ZOOM_IDLE)
        {
            destAlbum = (Rectangle){SCREEN_WIDTH/2 - 250, SCREEN_HEIGHT/2 - 250, 500, 500};
            albumPastOpen = true;
        }
        else if(albumPastOpen && !CheckCollisionPointRec(GetMousePosition(), destAlbum) && zoom.state == ZOOM_IDLE)
        {
            destAlbum = (Rectangle){SCREEN_WIDTH - 150, SCREEN_HEIGHT - 150, 100, 100};
            albumPastOpen = false;
        }
        
        if (albumPastOpen && !IsPuzzle1PastComplete)
        {
            Rectangle symbol1 = {740, 280, 30, 30};
            Rectangle symbol2 = {775, 280, 30, 30};
            Rectangle symbol3 = {810, 280, 30, 30};
            
            if (CheckCollisionPointRec(mouse, symbol1))
            {
                AddInput(&symbolSequenceP1, 1);
            }
            else if (CheckCollisionPointRec(mouse, symbol2))
            {
                AddInput(&symbolSequenceP1, 2);
            }
            else if (CheckCollisionPointRec(mouse, symbol3))
            {
                AddInput(&symbolSequenceP1, 3);
            }
        }
    }
    
    if (!IsPuzzle1PastComplete && albumPastOpen)
    {
        UpdateSequencePuzzle(&symbolSequenceP1);
        IsPuzzle1PastComplete = SequenceComplete(&symbolSequenceP1);
        if (IsPuzzle1PastComplete)
        {
            timerCaption = 0.0f;
            UnloadTexture(bgPastP1);
            bgPastP1 = LoadTexture("../assets/room0/mainhall-2_room0_past.jpg");
            InitZoomSystem(&zoom, bgPastP1);
        }
    }
    else if (IsPuzzle1PastComplete && !captionPuzzle1PastFinish)
    {
        timerCaption += GetFrameTime();
        if (captionPastIndex == 0 && timerCaption >= 0.0f)
        {
            captionPastIndex += 1;
            ShowCaption(&captionPast, "The clock... It worked.", 2.0f);
        }
        else if (captionPastIndex == 1 && timerCaption > 2.0f)
        {
            captionPastIndex += 1;
            ShowCaption(&captionPast, "And this photo... why is only my son circled?", 3.0f);
        }
        else if (captionPastIndex == 2 && timerCaption > 5.0f)
        {
            captionPastIndex += 1;
            ShowCaption(&captionPast, "..Is something going to happen to him?", 3.0f);
            
        }
        
        if (!captionPuzzle1PastFinish && timerCaption > 9.0f)
        {
            captionPuzzle1PastFinish = true;
            captionPastIndex = 0;
        }
    }
    
    if (captionPuzzle1PastFinish && IsPuzzle1PastComplete && zoom.state == ZOOM_IDLE)
    {
        game.currentLevel = 2;
        SaveGameFunc();
        
        ChangeScene(SCENE_PUZZLE2);
    }
    
    UpdateZoomSystem(&zoom);
    UpdateCaption(&captionPast);
}

void DrawPuzzle1PastScene()
{
    ClearBackground(BLACK);
    
    DrawZoomSystem(&zoom);
    
    if(zoom.state == ZOOM_IDLE)
    {
        if(albumPastOpen)
        {
            DrawRectangle(0, 0, SCREEN_WIDTH,SCREEN_HEIGHT, Fade(BLACK, 0.5f));
        }
        else 
        {
            DrawRectangle(destAlbum.x - 5, destAlbum.y - 5, destAlbum.width + 10, destAlbum.height + 10, Fade(BLACK, 0.3f));
        }
        DrawTexturePro(albumTexture, sourceAlbum, destAlbum, (Vector2){0, 0}, 0.0f, WHITE);
        
        if(IsPuzzle1PastComplete && albumPastOpen)
        {
            DrawTexturePro(photo1Album, (Rectangle){0, 0, photo1Album.width, photo1Album.height}, (Rectangle){682, 130, 300, (300 * photo1Album.height/photo1Album.width)}, (Vector2){0, 0}, 2.0f, WHITE);
        }
    }
    
    
    DrawCaption(&captionPast);
    //DrawText(TextFormat("seqLength: %d", symbolSequenceP1.sequenceLength), 100, 100, 20, RED);
    //DrawText(TextFormat("inputLength: %d", symbolSequenceP1.inputLength), 100, 200, 20, RED);
}

void UnloadPuzzle1PastScene()
{
    UnloadTexture(bgPastP1);
    UnloadTexture(candleZoom);
    UnloadTexture(roundpicZoom);
    UnloadTexture(telephoneZoom);
    UnloadTexture(albumTexture);
    UnloadTexture(photo1Album);
}