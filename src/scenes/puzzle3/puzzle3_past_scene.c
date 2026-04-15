/**
 * File: puzzle3_past_scene.c
 * Description:
 * Handles the logic and rendering for Puzzle 3 PAST Scene.
 * This room contains pictures assets, sequence puzzle, interactable item.
 *
 * Responsibilities:
 * - Initialize textures.
 * - Handle zoom system, sequence symbol puzzle, and interactable item
 * using box for drag and rotation.
 *
 *
 *
 */
 
#include "raylib.h"
#include "../../utils/constants.h"
#include "../../core/game.h"
#include "../../core/scene_manager.h"
#include "../../systems/sequence_system.h"
#include "../../systems/caption_system.h"
#include "../../systems/save_system.h"
#include "../../objects/box.h"

#define DIGIT_COUNT 9

typedef enum {
    BOX_IDLE,
    BOX_CORRECT,
    BOX_FLASH,
    BOX_FINISHED
} ItemPuzzle3State;

ItemPuzzle3State itemState = BOX_IDLE;

Rectangle itemPlace1 = {240, 497, 150, 150};
Rectangle itemPlace2 = {400, 497, 150, 150};
Rectangle itemPlace3 = {575, 497, 150, 150};

float flashTimer = 0.0f;
float flashDuration = 0.8f;
float flashAlpha = 0.0f;

int placedDigit[3] = {-1, -1, -1}; 
// index digit yang masuk ke slot 1,2,3

bool slotFilled[3] = {false, false, false};
bool puzzleNumberP3Complete = false;

Texture2D bgPuzzle3Past, albumTextureP3, photo1AlbumP3, photo2AlbumP3, boxDigit1, boxDigit2, boxDigit3, boxDigit4, boxDigit5, boxDigit6, boxDigit7, boxDigit8, boxDigit9, symbolPhoto3, photo3AlbumP3;
Rectangle sourceAlbumP3;
Rectangle destAlbumP3;

bool albumPastPuzzle3Open = false;
bool IsPuzzle3PastComplete = false;

Box digitItem[DIGIT_COUNT];
int activeDigitIndex = -1;

Rectangle symbol1P3 = {750, 380, 45, 40};
Rectangle symbol2P3 = {755, 427, 45, 42};
Rectangle symbol3P3 = {760, 478, 45, 42};
      
SymbolPuzzle symbolSequenceP3Past;        

void InitPuzzle3PastScene()
{
    slotFilled[3] = (bool){false, false, false};
    puzzleNumberP3Complete = false;
    albumPastPuzzle3Open = false;
    IsPuzzle3PastComplete = false;

    bgPuzzle3Past = LoadTexture("../assets/puzzle3/past/background_puzzle3_past.png");
    
    albumTextureP3 = LoadTexture("../assets/room0/artboard-album_room0_past.png");
    photo1AlbumP3 = LoadTexture("../assets/room0/photo1-album_room0_past.png");
    photo2AlbumP3 = LoadTexture("../assets/puzzle2/photo2_puzzle2_past.png");
    photo3AlbumP3 = LoadTexture("../assets/puzzle3/past/photo3_puzzle3_past.png");
    symbolPhoto3 = LoadTexture("../assets/puzzle3/past/symbol_puzzle3_past.png");
    
    sourceAlbumP3 = (Rectangle){0, 0, albumTextureP3.width, albumTextureP3.height};
    destAlbumP3 = (Rectangle){SCREEN_WIDTH - 160, SCREEN_HEIGHT - 160, 120, 120};
    
    boxDigit1 = LoadTexture("../assets/puzzle3/past/digit1.png");
    boxDigit2 = LoadTexture("../assets/puzzle3/past/digit2.png");
    boxDigit3 = LoadTexture("../assets/puzzle3/past/digit3.png");
    boxDigit4 = LoadTexture("../assets/puzzle3/past/digit4.png");
    boxDigit5 = LoadTexture("../assets/puzzle3/past/digit5.png");
    boxDigit6 = LoadTexture("../assets/puzzle3/past/digit6.png");
    boxDigit7 = LoadTexture("../assets/puzzle3/past/digit7.png");
    boxDigit8 = LoadTexture("../assets/puzzle3/past/digit8.png");
    boxDigit9 = LoadTexture("../assets/puzzle3/past/digit9.png");
    
    // INIT BOX 
    digitItem[0].textureTop = boxDigit1;
    digitItem[0].textureBottom = boxDigit1;
    
    digitItem[1].textureTop = boxDigit2;
    digitItem[1].textureBottom = boxDigit2;
    
    digitItem[2].textureTop = boxDigit3;
    digitItem[2].textureBottom = boxDigit3;
    
    digitItem[3].textureTop = boxDigit4;
    digitItem[3].textureBottom = boxDigit4;
    
    digitItem[4].textureTop = boxDigit5;
    digitItem[4].textureBottom = boxDigit5;
    
    digitItem[5].textureTop = boxDigit6;
    digitItem[5].textureBottom = boxDigit6;
    
    digitItem[6].textureTop = boxDigit7;
    digitItem[6].textureBottom = boxDigit7;
    
    
    digitItem[7].textureTop = boxDigit8;
    digitItem[7].textureBottom = boxDigit8;
    
    digitItem[8].textureTop = boxDigit9;
    digitItem[8].textureBottom = boxDigit9;
    
    for(int i = 0; i < DIGIT_COUNT; i++)
    {
        digitItem[i].position = (Vector2){400 + i * GetRandomValue(-20, 150), 400 + i * GetRandomValue(-5, 40)};
        digitItem[i].rotation = GetRandomValue(-7, 7);
        digitItem[i].targetWidth = 150;
    }
    
    symbolSequenceP3Past.sequence[0] = 3;
    symbolSequenceP3Past.sequence[1] = 1;
    symbolSequenceP3Past.sequence[2] = 2;
    symbolSequenceP3Past.sequence[3] = 3;
    symbolSequenceP3Past.sequence[4] = 2;
    symbolSequenceP3Past.sequence[5] = 3;
    
    symbolSequenceP3Past.sequenceLength = 6;
    
    InitSequencePuzzle(&symbolSequenceP3Past, 6);
}

void UpdatePuzzle3PastScene()
{
    for(int i = DIGIT_COUNT-1; i >= 0; i--)
    {
        Rectangle hitbox = {
            digitItem[i].position.x - 150,
            digitItem[i].position.y - 150,
            240,
            240
        };

        if(CheckCollisionPointRec(GetMousePosition(), hitbox))
        {
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
            {
                activeDigitIndex = i;
                break;
            }
        }
    }
    
    for(int i = 0; i < DIGIT_COUNT; i++)
    {
        if(i == activeDigitIndex)
            UpdateBox(&digitItem[i]);
    }
    
    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        activeDigitIndex = -1;
    }
    
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();
        
        if(!albumPastPuzzle3Open && CheckCollisionPointRec(GetMousePosition(), destAlbumP3))
        {
            destAlbumP3 = (Rectangle){SCREEN_WIDTH/2 - 250, SCREEN_HEIGHT/2 - 250, 500, 500};
            albumPastPuzzle3Open = true;
        }
        else if(albumPastPuzzle3Open && !CheckCollisionPointRec(GetMousePosition(), destAlbumP3))
        {
            destAlbumP3 = (Rectangle){SCREEN_WIDTH - 150, SCREEN_HEIGHT - 150, 100, 100};
            albumPastPuzzle3Open = false;
        }
        
        if(activeDigitIndex != -1)
        {
            Vector2 pos = digitItem[activeDigitIndex].position;

            // SLOT 1
            if(CheckCollisionPointRec(pos, itemPlace1))
            {
                if (activeDigitIndex == 2) 
                {
                    placedDigit[0] = 2;
                    slotFilled[0] = true;

                    digitItem[2].position = (Vector2){itemPlace1.x + itemPlace1.width/2,itemPlace1.y + itemPlace1.height/2};
                    digitItem[2].rotation = 0.0f;
                }
                
            }
            // SLOT 2
            else if(CheckCollisionPointRec(pos, itemPlace2))
            {
                if (activeDigitIndex == 3)
                {
                    placedDigit[1] = 3;
                    slotFilled[1] = true;

                    digitItem[3].position = (Vector2){itemPlace2.x + itemPlace2.width/2,itemPlace2.y + itemPlace2.height/2};
                    digitItem[3].rotation = 0.0f;
                }
                
            }
            // SLOT 3
            else if(CheckCollisionPointRec(pos, itemPlace3))
            {
                if (activeDigitIndex == 6)
                {
                    placedDigit[2] = 6;
                    slotFilled[2] = true;

                    digitItem[6].position = (Vector2){itemPlace3.x + itemPlace3.width/2,itemPlace3.y + itemPlace3.height/2};
                    digitItem[6].rotation = 0.0f;
                }
                
            }
        }

        //activeDigitIndex = -1;
        
        
        if (albumPastPuzzle3Open && !IsPuzzle3PastComplete)
        {
            
            if (CheckCollisionPointRec(mouse, symbol1P3))
            {
                AddInput(&symbolSequenceP3Past, 1);
            }
            else if (CheckCollisionPointRec(mouse, symbol2P3))
            {
                AddInput(&symbolSequenceP3Past, 2);
            }
            else if (CheckCollisionPointRec(mouse, symbol3P3))
            {
                AddInput(&symbolSequenceP3Past, 3);
            }
        }
    }
    
    if(!puzzleNumberP3Complete)
    {
        if(slotFilled[0] && slotFilled[1] && slotFilled[2])
        {
            if(placedDigit[0] == 2 &&  // 3
               placedDigit[1] == 3 &&  // 4
               placedDigit[2] == 6)    // 7
            {
                itemState = BOX_FLASH;
                flashTimer = 0.0f;
                puzzleNumberP3Complete = true;
            }
            else
            {
                // reset kalau salah
                for(int i = 0; i < 3; i++)
                {
                    slotFilled[i] = false;
                    placedDigit[i] = -1;
                }
            }
        }
    }
    
    if(itemState == BOX_FLASH)
    {
        flashTimer += GetFrameTime();
        flashAlpha = flashTimer / flashDuration;

        if(flashAlpha > 1.0f) flashAlpha = 1.0f;

        if(flashTimer >= flashDuration)
        {
            itemState = BOX_FINISHED;
        }
    }
    
    if (albumPastPuzzle3Open && !IsPuzzle3PastComplete)
    {
        UpdateSequencePuzzle(&symbolSequenceP3Past);
        IsPuzzle3PastComplete = symbolSequenceP3Past.solved;
    }
    else if (symbolSequenceP3Past.solved && !IsPuzzle3PastComplete)
    {
        IsPuzzle3PastComplete = true;
    }
    
    // MENUJU ENDING
    if (symbolSequenceP3Past.solved && !albumPastPuzzle3Open)
    {
        game.currentLevel = 4;
        SaveGameFunc();
        
        ChangeScene(SCENE_PUZZLE4);
    }   
}

void DrawPuzzle3PastScene()
{
    ClearBackground(BLACK);
    
    DrawTexturePro(bgPuzzle3Past, (Rectangle){0, 0, bgPuzzle3Past.width, bgPuzzle3Past.height}, (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, (Vector2){0, 0}, 0.0f, WHITE);
    
    if(itemState != BOX_FINISHED)
    {
        for(int i = 0; i < DIGIT_COUNT; i++)
        {
            DrawBox(&digitItem[i]);
        }
    }
    else
    {
        DrawTexturePro(boxDigit3, (Rectangle){0, 0, boxDigit3.width, boxDigit3.height}, (Rectangle){itemPlace1.x, itemPlace1.y, 150, 150}, (Vector2){0, 0}, 0.0f, WHITE);
        DrawTexturePro(boxDigit4, (Rectangle){0, 0, boxDigit4.width, boxDigit4.height}, (Rectangle){itemPlace2.x, itemPlace2.y, 150, 150}, (Vector2){0, 0}, 0.0f, WHITE);
        DrawTexturePro(boxDigit7, (Rectangle){0, 0, boxDigit7.width, boxDigit7.height}, (Rectangle){itemPlace3.x, itemPlace3.y, 150, 150}, (Vector2){0, 0}, 0.0f, WHITE);
        
        DrawTexturePro(symbolPhoto3, (Rectangle){0, 0, symbolPhoto3.width, symbolPhoto3.height}, (Rectangle){600, 300, 330, (330 * symbolPhoto3.height/symbolPhoto3.width)}, (Vector2){0, 0}, 0.0f, WHITE);
    }
    
    if(albumPastPuzzle3Open)
    {
        DrawRectangle(0, 0, SCREEN_WIDTH,SCREEN_HEIGHT, Fade(BLACK, 0.5f));
            
        DrawTexturePro(albumTextureP3, sourceAlbumP3, destAlbumP3, (Vector2){0, 0}, 0.0f, WHITE);
            
        DrawTexturePro(photo1AlbumP3, (Rectangle){0, 0, photo1AlbumP3.width, photo1AlbumP3.height}, (Rectangle){682, 130, 300, (300 * photo1AlbumP3.height/photo1AlbumP3.width)}, (Vector2){0, 0}, 2.0f, WHITE);
        
        if (IsPuzzle3PastComplete)
        {
            DrawTexturePro(photo3AlbumP3, (Rectangle){0, 0, photo3AlbumP3.width, photo3AlbumP3.height}, (Rectangle){680, 350, 300, (300 * photo3AlbumP3.height/photo3AlbumP3.width)}, (Vector2){0, 0}, -1.0f, WHITE);
        }
            
        DrawTexturePro(photo2AlbumP3, (Rectangle){0, 0, photo2AlbumP3.width, photo2AlbumP3.height}, (Rectangle){285, 55, 320, (320 * photo2AlbumP3.height/photo2AlbumP3.width)}, (Vector2){0, 0}, -1.7f, WHITE);
            
        
        
    }
    else 
    {
        DrawRectangle(destAlbumP3.x - 5, destAlbumP3.y - 5, destAlbumP3.width + 10, destAlbumP3.height + 10, Fade(BLACK, 0.3f));
        DrawTexturePro(albumTextureP3, sourceAlbumP3, destAlbumP3, (Vector2){0, 0}, 0.0f, WHITE);
    }
    
    if(itemState == BOX_FLASH)
    {
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(WHITE, flashAlpha));
    }
    
    
    
    //DrawRectangleRec(itemPlace1, WHITE);
    //DrawRectangleRec(itemPlace2, WHITE);
    //DrawRectangleRec(itemPlace3, WHITE);
}

void UnloadPuzzle3PastScene()
{
}