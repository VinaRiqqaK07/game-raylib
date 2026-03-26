#include "raylib.h"
#include "room0_past_scene.h"
#include "../../utils/constants.h"
#include "../../core/game.h"
#include "../../core/scene_manager.h"
#include "../../systems/ui_system.h"
#include "../../systems/zoom_system.h"
#include "../../systems/sequence_system.h"
#include "../../systems/caption_system.h"

Texture2D introRoomPast, candleZoom, roundpicZoom, teasetZoom, telephoneZoom, shelfZoom, albumTexture, photo1Album;
Rectangle sourceRoomPast;
Rectangle destRoomPast;
Rectangle sourceAlbum;
Rectangle destAlbum;

Rectangle zoomCandle = {450, 250, 100, 100};
Rectangle roundPic = {30, 178, 120, 260};
Rectangle teaSet = {365, 470, 130, 100};
Rectangle telephone = {770, 450, 90, 90};
Rectangle shelf = {880, 330, 150, 200};

Rectangle symbol1 = {740, 280, 30, 30};
Rectangle symbol2 = {775, 280, 30, 30};
Rectangle symbol3 = {810, 280, 30, 30};

bool albumPastOpen = false;
ZoomSystem zoom;

SymbolPuzzle symbolSequenceP1;
bool IsPuzzle1PastComplete = false;

Caption captionPast;
bool captionPuzzle1PastFinish = false;
float timerCaption = 0.0f;
int captionPastIndex = 0;

void InitRoom0Past()
{
    introRoomPast = LoadTexture("../assets/mainhall_room0_past.jpg");
    candleZoom = LoadTexture("../assets/candle_room0_past.jpg");
    roundpicZoom = LoadTexture("../assets/round-pic_room0_past.jpg");
    teasetZoom = LoadTexture("../assets/tea-set_room0_past.jpg");
    telephoneZoom = LoadTexture("../assets/telephone_room0_past.jpg");
    shelfZoom = LoadTexture("../assets/shelf_room0_past.jpg");
    
    albumTexture = LoadTexture("../assets/room0/artboard-album_room0_past.png");
    photo1Album = LoadTexture("../assets/room0/photo1-album_room0_past.png");
    
    sourceRoomPast = (Rectangle){0, 0, introRoomPast.width, introRoomPast.height};
    destRoomPast = (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    
    sourceAlbum = (Rectangle){0, 0, albumTexture.width, albumTexture.height};
    destAlbum = (Rectangle){SCREEN_WIDTH - 160, SCREEN_HEIGHT - 160, 120, 120};
    
    InitZoomSystem(&zoom, introRoomPast);
    
    symbolSequenceP1.sequence[0] = 1;
    symbolSequenceP1.sequence[1] = 2;
    symbolSequenceP1.sequence[2] = 2;
    symbolSequenceP1.sequence[3] = 3;
    symbolSequenceP1.sequence[4] = 1;
    InitSequencePuzzle(&symbolSequenceP1);
    
    InitCaptionSystem(&captionPast);
}

void UpdateRoom0Past()
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
        else if(CheckCollisionPointRec(mouse, teaSet)&& zoom.state == ZOOM_IDLE && !albumPastOpen)
        {
            TriggerZoom(&zoom, teasetZoom);
        }
        else if(CheckCollisionPointRec(mouse, telephone)&& zoom.state == ZOOM_IDLE && !albumPastOpen)
        {
            TriggerZoom(&zoom, telephoneZoom);
        }
        else if(CheckCollisionPointRec(mouse, shelf)&& zoom.state == ZOOM_IDLE && !albumPastOpen)
        {
            TriggerZoom(&zoom, shelfZoom);
        }
        
        if(CheckCollisionPointRec(GetMousePosition(), destAlbum) && zoom.state == ZOOM_IDLE)
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
    
    if (!IsPuzzle1PastComplete)
    {
        UpdateSequencePuzzle(&symbolSequenceP1);
        IsPuzzle1PastComplete = SequenceComplete(&symbolSequenceP1);
        if (IsPuzzle1PastComplete)
        {
            timerCaption = 0.0f;
            introRoomPast = LoadTexture("../assets/room0/mainhall-2_room0_past.jpg");
            InitZoomSystem(&zoom, introRoomPast);
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
            captionPuzzle1PastFinish = true;
        }
        
        if (captionPuzzle1PastFinish)
        {
            captionPastIndex = 0;
        }
    }
    
    UpdateZoomSystem(&zoom);
    UpdateCaption(&captionPast);
}

void DrawRoom0Past()
{
    //DrawTexturePro(introRoomPast,sourceRoomPast,destRoomPast,(Vector2){0,0},0.0f,WHITE);
    //DrawText("PAST ROOM 0", 200, 150, 20, WHITE);
    
    DrawZoomSystem(&zoom);
    
    if(zoom.state == ZOOM_IDLE)
    {
        if(albumPastOpen)
        {
            DrawRectangle(0, 0, SCREEN_WIDTH,SCREEN_HEIGHT, Fade(BLACK, 0.8f));
        }
        else 
        {
            DrawRectangle(destAlbum.x - 5, destAlbum.y - 5, destAlbum.width + 10, destAlbum.height + 10, Fade(BLACK, 0.3f));
        }
        DrawTexturePro(albumTexture, sourceAlbum, destAlbum, (Vector2){0, 0}, 0.0f, WHITE);
        /*
        if(albumPastOpen)
        {
            DrawRectangleRec(symbol1, WHITE);
            DrawRectangleRec(symbol2, WHITE);
            DrawRectangleRec(symbol3, WHITE);
        }
        */
        
        if(IsPuzzle1PastComplete && albumPastOpen)
        {
            DrawTexturePro(photo1Album, (Rectangle){0, 0, photo1Album.width, photo1Album.height}, (Rectangle){682, 200, 200, (200 * photo1Album.height/photo1Album.width)}, (Vector2){0, 0}, 2.0f, WHITE);
        }
    }
    
    DrawCaption(&captionPast);
    //DrawRectangleRec(telephone, WHITE);
    
}

void UnloadRoom0Past()
{
}