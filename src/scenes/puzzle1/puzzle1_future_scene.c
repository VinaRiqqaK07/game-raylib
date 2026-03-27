#include "raylib.h"
#include "puzzle1_future_scene.h"
#include "../../utils/constants.h"
#include "../../core/game.h"
#include "../../core/scene_manager.h"
#include "../../systems/save_system.h"
#include "../../systems/zoom_system.h"
#include "../../systems/keypad_system.h"
#include "../../systems/sequence_system.h"

Texture2D introRoomFuture, tiltedPic, roundSafe, roundSafeKeypad, telephoneKeypad;
Rectangle sourceRoomFuture;
Rectangle destRoomFuture;

Rectangle tiltedPicArea = {320, 220, 140, 210};
Rectangle roundKeypadArea = {845, 325, 40, 65};
Rectangle telephoneArea = {785, 440, 100, 100};

bool tiltedPicShoved = false;
bool roundSafeShowed = false;
bool keypadShowed = false;
bool telephoneKeypadShowed = false;

ZoomSystem zoomFuture;
Keypad keypadRoundSafe;
KeypadButton telephoneButton[12];
int telephoneValue[12] = {9,3,1,9,9,9,9,9,9,2,9,4};

SymbolPuzzle telephoneSequenceP1;
bool IsPuzzle1FutureComplete = false;
bool adinput = false;

void InitPuzzle1FutureScene()
{
    introRoomFuture = LoadTexture("../assets/room0/mainhall-0_room0_future.jpg");
    tiltedPic = LoadTexture("../assets/room0/tilted-pic_room0_future.png");
    roundSafe = LoadTexture("../assets/room0/roundsafe-closed_room0_future.jpg");
    roundSafeKeypad = LoadTexture("../assets/room0/roundsafekeypad_room0_future.jpg");
    telephoneKeypad = LoadTexture("../assets/room0/telephone_room0_future.jpg");
    
    sourceRoomFuture = (Rectangle){0, 0, introRoomFuture.width, introRoomFuture.height};
    destRoomFuture = (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    
    InitZoomSystem(&zoomFuture, introRoomFuture);
    
    keypadRoundSafe.correctPassword = "617";
    keypadRoundSafe.maxLength = 3;
    keypadRoundSafe.panel = (Rectangle){140, 345, 78, 100};
    keypadRoundSafe.opening = true;
    keypadRoundSafe.isOpen = true;
    
    InitKeypad(&keypadRoundSafe);
    
    for (int i = 0; i < 12; i++)
    {
        int row = i / 3;
        int col = i % 3;

        telephoneButton[i].bounds = (Rectangle){
            795 + col * (55 + 8),
            196 + row * (55 + 8),
            55,
            55
        };

        telephoneButton[i].value = telephoneValue[i];
    }
    
    telephoneSequenceP1.sequence[0] = 1;
    telephoneSequenceP1.sequence[1] = 2;
    telephoneSequenceP1.sequence[2] = 3;
    telephoneSequenceP1.sequence[3] = 4;
    telephoneSequenceP1.sequenceLength = 4;
    InitSequencePuzzle(&telephoneSequenceP1, 4);
}

void UpdatePuzzle1FutureScene()
{
    if (zoomFuture.state == ZOOM_IDLE)
    {
        roundSafeShowed = false;
        keypadShowed = false;
        telephoneKeypadShowed = false;
    }
    
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();
        
        if(CheckCollisionPointRec(mouse, tiltedPicArea)&& zoomFuture.state == ZOOM_IDLE)
        {
            TriggerZoom(&zoomFuture, roundSafe);
            roundSafeShowed = true;
        }
        else if(CheckCollisionPointRec(mouse, (Rectangle){380, 0, 640, 680}) && !tiltedPicShoved && roundSafeShowed)
        {
            tiltedPicShoved = true;
        }
        else if(CheckCollisionPointRec(mouse, roundKeypadArea) && tiltedPicShoved && roundSafeShowed)
        {
            zoomFuture.state = ZOOM_IDLE;
            TriggerZoom(&zoomFuture, roundSafeKeypad);
            keypadShowed = true;
        }
        else if(CheckCollisionPointRec(mouse, telephoneArea)&& zoomFuture.state == ZOOM_IDLE && keypadRoundSafe.passwordCorrect && !IsPuzzle1FutureComplete)
        {
            TriggerZoom(&zoomFuture, telephoneKeypad);
            telephoneKeypadShowed = true;
        }
        else if(telephoneKeypadShowed)
        {
            for (int i = 0; i < 12; i++)
            {
                if(CheckCollisionPointRec(mouse, telephoneButton[i].bounds))
                {
                    AddInput(&telephoneSequenceP1, telephoneButton[i].value);
                    adinput = true;
                }
                
            }
            
            
        }
    }
    
    UpdateZoomSystem(&zoomFuture);
    if (keypadShowed)
    {
        UpdateKeypad(&keypadRoundSafe);
        if (keypadRoundSafe.passwordCorrect)
        {
            roundSafe = LoadTexture("../assets/room0/roundsafe-open_room0_future.jpg");
            InitZoomSystem(&zoomFuture, introRoomFuture);
        }
    }
    else if(telephoneKeypadShowed && !IsPuzzle1FutureComplete)
    {
        UpdateSequencePuzzle(&telephoneSequenceP1);
        IsPuzzle1FutureComplete = SequenceComplete(&telephoneSequenceP1);
        if (IsPuzzle1FutureComplete)
        {
            InitZoomSystem(&zoomFuture, introRoomFuture);
            //ChangeScene(SCENE_PUZZLE2);
        }
    }
    
    if (IsPuzzle1FutureComplete && zoomFuture.state == ZOOM_IDLE)
    {
        game.currentLevel = 2;
        SaveGameFunc();
        ChangeScene(SCENE_PUZZLE2);
    }
}


void DrawPuzzle1FutureScene()
{
    ClearBackground(BLACK);
    //DrawTexturePro(introRoomFuture,sourceRoomFuture,destRoomFuture,(Vector2){0,0},0.0f,WHITE);
    //DrawText("FUTURE ROOM 0", 200, 150, 20, WHITE);
    DrawZoomSystem(&zoomFuture);
    
    if (!tiltedPicShoved && roundSafeShowed && zoomFuture.state == ZOOMED)
    {
        DrawTexturePro(tiltedPic, (Rectangle){0, 0, tiltedPic.width, tiltedPic.height}, (Rectangle){380, 0, 640, 680}, (Vector2){0,0}, 3.0f,WHITE);
    }
    else if (keypadShowed && zoomFuture.state == ZOOMED && !keypadRoundSafe.passwordCorrect)
    {
        DrawKeypad(&keypadRoundSafe);
        //DrawRectangleRec(roundKeypadArea, WHITE);
    }
    
    if (IsPuzzle1FutureComplete)
    {
        DrawText("PUZZLLE 1 COMPLETE", 200, 150, 20, WHITE);
    }
    
    //DrawText(TextFormat("InputLength: %d", telephoneSequenceP1.inputLength), 100, 100, 20, RED);
    
    /*
    for (int i = 0; i < 12; i++)
    {
        DrawRectangleRec(telephoneButton[i].bounds, WHITE);
    }*/
    
    //DrawRectangleRec(telephoneArea, WHITE);
    
}

void UnloadPuzzle1FutureScene()
{
    UnloadTexture(introRoomFuture);
    UnloadTexture(tiltedPic);
    UnloadTexture(roundSafe);
    UnloadTexture(roundSafeKeypad);
    UnloadTexture(telephoneKeypad);
}