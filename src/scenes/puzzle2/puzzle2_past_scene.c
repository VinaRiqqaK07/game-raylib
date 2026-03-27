#include "raylib.h"
#include "../../utils/constants.h"
#include "../../core/game.h"
#include "../../core/scene_manager.h"
#include "../../systems/ui_system.h"
#include "../../systems/zoom_system.h"
#include "../../systems/sequence_system.h"
#include "../../systems/caption_system.h"
#include "../../systems/wiring_minigame.h"

Texture2D bgPuzzle2Past, wiringDetail, bwbuttonDetail, albumTextureP2, photo1AlbumP2;
Rectangle sourceAlbumP2;
Rectangle destAlbumP2;


ZoomSystem zoomPastP2;
WiringSystem wireMinigamePast;
SymbolPuzzle symbolSequenceP2Past;

Rectangle wiringArea = {940, 260, 50, 80};
Rectangle bwButtonArea = {490, 500, 30, 50};
Rectangle blackButtonArea = {600, 300, 55, 60};
Rectangle whiteButtonArea = {600, 370, 55, 60};

bool wireMinigameOpen = false;
bool bwButtonDetailOpen = false;
bool albumPastPuzzle2Open = false;

void InitPuzzle2PastScene()
{
    bgPuzzle2Past = LoadTexture("../assets/puzzle2/mainhall_puzzle2_past.jpg");
    wiringDetail = LoadTexture("../assets/puzzle2/wiring-detail_puzzle2_past.jpg");
    bwbuttonDetail = LoadTexture("../assets/puzzle2/bw-button_puzzle2_past.jpg");
    
    albumTextureP2 = LoadTexture("../assets/room0/artboard-album_room0_past.png");
    photo1AlbumP2 = LoadTexture("../assets/room0/photo1-album_room0_past.png");
    
    sourceAlbumP2 = (Rectangle){0, 0, albumTextureP2.width, albumTextureP2.height};
    destAlbumP2 = (Rectangle){SCREEN_WIDTH - 160, SCREEN_HEIGHT - 160, 120, 120};
    
    InitZoomSystem(&zoomPastP2, bgPuzzle2Past);
    
    InitWiring(&wireMinigamePast);
    
    symbolSequenceP2Past.sequence[0] = 1;
    symbolSequenceP2Past.sequence[1] = 2;
    symbolSequenceP2Past.sequence[2] = 2;
    symbolSequenceP2Past.sequence[3] = 1;
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
        else if(CheckCollisionPointRec(mouse, bwButtonArea)&& zoomPastP2.state == ZOOM_IDLE && wireMinigamePast.completed && !symbolSequenceP2Past.solved)
        {
            TriggerZoom(&zoomPastP2, bwbuttonDetail);
            bwButtonDetailOpen = true;
        }
        
        if (bwButtonDetailOpen)
        {
            if(CheckCollisionPointRec(mouse, blackButtonArea)&& !symbolSequenceP2Past.solved)
            {
                AddInput(&symbolSequenceP2Past, 1);
            }
            else if(CheckCollisionPointRec(mouse, whiteButtonArea)&& !symbolSequenceP2Past.solved)
            {
                AddInput(&symbolSequenceP2Past, 2);
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
    
    if (bwButtonDetailOpen && !symbolSequenceP2Past.solved)
    {
        UpdateSequencePuzzle(&symbolSequenceP2Past);
    }
    else if (bwButtonDetailOpen && symbolSequenceP2Past.solved)
    {
        InitZoomSystem(&zoomPastP2, bgPuzzle2Past);
    }
    
    UpdateZoomSystem(&zoomPastP2);
    
}

void DrawPuzzle2PastScene()
{
    //DrawTexturePro(introRoomPast,sourceRoomPast,destRoomPast,(Vector2){0,0},0.0f,WHITE);
    //DrawText("PAST ROOM 0", 200, 150, 20, WHITE);
    
    DrawZoomSystem(&zoomPastP2);
    //DrawText("PAST PUZZLE 2", 200, 150, 20, WHITE);
    
    if (wireMinigameOpen && !wireMinigamePast.completed && zoomPastP2.state == ZOOMED)
    {
        DrawWiring(&wireMinigamePast);
    }
    /*
    if (bwButtonDetailOpen)
    {
        //DrawRectangleRec(blackButtonArea, WHITE);
        //DrawRectangleRec(whiteButtonArea, WHITE);
    }*/
    
    if(zoomPastP2.state == ZOOM_IDLE)
    {
        if(albumPastPuzzle2Open)
        {
            DrawRectangle(0, 0, SCREEN_WIDTH,SCREEN_HEIGHT, Fade(BLACK, 0.5f));
            
            DrawTexturePro(albumTextureP2, sourceAlbumP2, destAlbumP2, (Vector2){0, 0}, 0.0f, WHITE);
            
            DrawTexturePro(photo1AlbumP2, (Rectangle){0, 0, photo1AlbumP2.width, photo1AlbumP2.height}, (Rectangle){682, 200, 200, (200 * photo1AlbumP2.height/photo1AlbumP2.width)}, (Vector2){0, 0}, 2.0f, WHITE);
        }
        else 
        {
            DrawRectangle(destAlbumP2.x - 5, destAlbumP2.y - 5, destAlbumP2.width + 10, destAlbumP2.height + 10, Fade(BLACK, 0.3f));
            DrawTexturePro(albumTextureP2, sourceAlbumP2, destAlbumP2, (Vector2){0, 0}, 0.0f, WHITE);
        }
        
        /*
        if(IsPuzzle1PastComplete && albumPastOpen)
        {
            
        }*/
    }
    
    //DrawRectangleRec(bwButtonArea, WHITE);
    
    
    //DrawWiring(&wireMinigamePast);
    //DrawRectangleRec(wiringArea, WHITE);
    
}

void UnloadPuzzle2PastScene()
{
    UnloadTexture(bgPuzzle2Past);
}