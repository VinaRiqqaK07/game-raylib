/**
 * File: puzzle2_future_scene.c
 * Description:
 * Handles the logic and rendering for Puzzle 2 FUTURE role Scene.
 * This room contains pictures assets, zoom system, and connect minigame.
 *
 * Responsibilities:
 * - Initialize textures.
 * - Handle zoom system, sequence symbol puzzle, and connect minigame.
 *
 *
 *
 */
 
#include "raylib.h"
#include "../../utils/constants.h"
#include "../../core/game.h"
#include "../../core/scene_manager.h"
#include "../../systems/zoom_system.h"
#include "../../systems/keypad_system.h"
#include "../../systems/sequence_system.h"
#include "../../systems/save_system.h"
#include "../../systems/connect_minigame.h"

Texture2D bgPuzzle2Future, shelfFutureP2, telephoneP2Detail;

ZoomSystem zoomFutureP2;
ConnectGridPuzzle gridPuzzleFutureP2;

Rectangle shelfAreaP2 = {30, 200, 150, 220};
Rectangle telephoneAreaP2 = {785, 440, 100, 100};
bool shelfDetailedP2Open = false;
bool telephoneP2Showed = false;

KeypadButton telephoneButtonP2[12];
int telephoneP2Value[12] = {9,2,9,4,9,9,1,9,9,9,3,9};
SymbolPuzzle telephoneSequenceP2;

bool IsConnectP2Complete = false;
bool IsPuzzle2FutureComplete = false;

void InitPuzzle2FutureScene()
{
    bgPuzzle2Future = LoadTexture("../assets/puzzle2/mainhall_room0_future.jpg");
    shelfFutureP2 = LoadTexture("../assets/puzzle2/pigura_puzzle2_future.png");
    telephoneP2Detail = LoadTexture("../assets/room0/telephone_room0_future.jpg");
    
    InitZoomSystem(&zoomFutureP2, bgPuzzle2Future);
    InitConnectGrid(&gridPuzzleFutureP2);
    
    for (int i = 0; i < 12; i++)
    {
        int row = i / 3;
        int col = i % 3;

        telephoneButtonP2[i].bounds = (Rectangle){
            795 + col * (55 + 8),
            196 + row * (55 + 8),
            55,
            55
        };

        telephoneButtonP2[i].value = telephoneP2Value[i];
    }
    
    telephoneSequenceP2.sequence[0] = 1;
    telephoneSequenceP2.sequence[1] = 2;
    telephoneSequenceP2.sequence[2] = 3;
    telephoneSequenceP2.sequence[3] = 4;
    telephoneSequenceP2.sequenceLength = 4;
    InitSequencePuzzle(&telephoneSequenceP2, 4);
}

void UpdatePuzzle2FutureScene()
{
    if (zoomFutureP2.state == ZOOM_IDLE)
    {
        shelfDetailedP2Open = false;
        telephoneP2Showed = false;
    }
    
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();
        
        if(CheckCollisionPointRec(mouse, shelfAreaP2)&& zoomFutureP2.state == ZOOM_IDLE && !IsConnectP2Complete)
        {
            TriggerZoom(&zoomFutureP2, shelfFutureP2);
            shelfDetailedP2Open = true;
        }
        else if(CheckCollisionPointRec(mouse, telephoneAreaP2)&& zoomFutureP2.state == ZOOM_IDLE && !IsPuzzle2FutureComplete && IsConnectP2Complete)
        {
            TriggerZoom(&zoomFutureP2, telephoneP2Detail);
            telephoneP2Showed = true;
        }
        else if(telephoneP2Showed)
        {
            for (int i = 0; i < 12; i++)
            {
                if(CheckCollisionPointRec(mouse, telephoneButtonP2[i].bounds))
                {
                    AddInput(&telephoneSequenceP2, telephoneButtonP2[i].value);  
                }
                
            }
        }
    }
    
    if (shelfDetailedP2Open && !IsConnectP2Complete)
    {
        int offsetX = 400;   // posisi grid di layar (atur sendiri)
        int offsetY = 200;
        int cellSize = 80;

        Node gridPos = GetGridPos(GetMousePosition(), offsetX, offsetY, cellSize);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            TryStartDrag(&gridPuzzleFutureP2, gridPos);
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            UpdateConnectGrid(&gridPuzzleFutureP2, gridPos);
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            gridPuzzleFutureP2.dragging = false;
            gridPuzzleFutureP2.activePair = -1;
        }
        
        IsConnectP2Complete = IsPuzzleComplete(&gridPuzzleFutureP2);

        if (IsConnectP2Complete)
        {
            UnloadTexture(bgPuzzle2Future);
            bgPuzzle2Future = LoadTexture("../assets/puzzle2/mainhall-2_puzzle2_future.jpg");
            InitZoomSystem(&zoomFutureP2, bgPuzzle2Future);
        }
    }
    
    
    UpdateZoomSystem(&zoomFutureP2);
    
    if(telephoneP2Showed && !IsPuzzle2FutureComplete && IsConnectP2Complete)
    {
        UpdateSequencePuzzle(&telephoneSequenceP2);
        IsPuzzle2FutureComplete = SequenceComplete(&telephoneSequenceP2);
    }
    
    if (telephoneSequenceP2.solved)
    {
        game.currentLevel = 3;
        SaveGameFunc();
        
        ChangeScene(SCENE_PUZZLE3);
    }
}


void DrawPuzzle2FutureScene()
{
    ClearBackground(BLACK);
    
    DrawZoomSystem(&zoomFutureP2);
    
    
    if (shelfDetailedP2Open && zoomFutureP2.state == ZOOMED)
    {
        DrawConnectGrid(&gridPuzzleFutureP2);
    }
    
    
}

void UnloadPuzzle2FutureScene()
{
    UnloadTexture(bgPuzzle2Future);
    UnloadTexture(shelfFutureP2);
    UnloadTexture(telephoneP2Detail);
}