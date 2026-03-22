#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include "room1_future_scene.h"
#include "../../utils/constants.h"
#include "../../core/game.h"
#include "../../core/scene_manager.h"
#include "../../systems/ui_system.h"
#include "../../systems/keypad_system.h"

/*
#define MAX_PASS 3

char password[MAX_PASS+1] = "\0";
int passLength = 0;

bool opening = false;
bool keypadOpen = false;
bool opened = false;
float animSpeed = 4.0f;

typedef struct {
    Rectangle bounds;
    int value;
} KeypadButton;

KeypadButton keypad[12];
Rectangle closeButton;

int startXkeypad = 300;
int startYkeypad = 250;
int size = 70;
int gap = 10;
Rectangle keypadTarget = {300, 250, 240, 320};
Rectangle keypadPanel = {140, 345, 78, 100};
Rectangle keypadStart;

int numbers[10] = {1,2,3,4,5,6,7,8,9,0};
const char correctPassword[] = "235";
bool passwordEntered = false;
bool passwordCorrect = false;
*/

Keypad keypad;
Texture2D clock, clockFinish, board;

void InitRoom1Future()
{
    clock = LoadTexture("../assets/puzzle1/clock_puzzle1_future.png");
    clockFinish = LoadTexture("../assets/puzzle1/clock-finish_puzzle1_future.png");
    board = LoadTexture("../assets/puzzle1/board_puzzle1_future.png");
    
    keypad.correctPassword = "235";
    keypad.maxLength = 3;
    keypad.panel = (Rectangle){140, 345, 78, 100};
    
    InitKeypad(&keypad);
    /*
    
    closeButton = (Rectangle){
        startXkeypad + keypadTarget.width - 30,
        startYkeypad - (size + 50),
        30,
        30
    };
    keypadStart = keypadPanel;*/
}

void UpdateRoom1Future()
{
    UpdateKeypad(&keypad);
    /*
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(GetMousePosition(), keypadPanel))
        {
            opening = true;
            keypadOpen = true;
        }
        else if (CheckCollisionPointRec(GetMousePosition(), closeButton))
        {
            opening = false; 
            keypadOpen = false; // atau state kamu untuk menutup
        }
    }
        
    
    
    if (opening)
    {
        
        keypadPanel.x += (keypadTarget.x - keypadPanel.x) * 0.1f;
        keypadPanel.y += (keypadTarget.y - keypadPanel.y) * 0.1f;
        keypadPanel.width += (keypadTarget.width - keypadPanel.width) * 0.1f;
        keypadPanel.height += (keypadTarget.height - keypadPanel.height) * 0.1f;
    }
    else
    {
        keypadPanel.x += (keypadStart.x - keypadPanel.x) * 0.1f;
        keypadPanel.y += (keypadStart.y - keypadPanel.y) * 0.1f;
        keypadPanel.width += (keypadStart.width - keypadPanel.width) * 0.1f;
        keypadPanel.height += (keypadStart.height - keypadPanel.height) * 0.1f;
    }
    
    if (keypadPanel.width > 200)
    {
        keypadOpen = true;
        UpdateKeypad(); 
    }
    else
    {
        keypadOpen = false;
    }*/
}


void DrawRoom1Future()
{
    DrawText("FUTURE PUZZLE LEVEL 1", 100, 20, 20, WHITE);
    
    if (keypad.passwordCorrect == true)
    {
        DrawTextureEx(clockFinish, (Vector2){100, 50}, 0.0f, 0.3f, WHITE);
    }else
    {
        DrawTextureEx(clock, (Vector2){100, 50}, 0.0f, 0.3f, WHITE);
    }
    
    DrawTextureEx(board, (Vector2){600, 100}, -5.0f, 0.3f, WHITE);
    
    if (keypad.panel.width > 200)
    {
        DrawRectangle(0, 0, SCREEN_WIDTH,SCREEN_HEIGHT, Fade(BLACK, 0.7f));
        DrawKeypad(&keypad);
    }
    else
    {
        DrawRectangleRec(keypad.panel, DARKGRAY);
        DrawRectangleLinesEx(keypad.panel, 3, WHITE);    
    }
}
/*
void UpdateKeypad()
{
    // Keyboard keypad input
    int key = GetKeyPressed();

    if (key >= KEY_ZERO && key <= KEY_NINE)
    {
        if (passLength < MAX_PASS)
        {
            password[passLength++] = '0' + (key - KEY_ZERO);
            password[passLength] = '\0';
        }
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        passLength--;
        if (passLength < 0) passLength = 0;
        password[passLength] = '\0';
        passwordEntered = false;
    }
    
    //Mouse keypad input
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        for (int i = 0; i < 12; i++)
        {
            if (CheckCollisionPointRec(mouse, keypad[i].bounds))
            {
                if (i > 9)
                {
                    if (i == 10)
                    {
                        passLength = 0;
                        if (passLength < 0) passLength = 0;
                        password[passLength] = '\0';
                        passwordEntered = false;
                    }
                    if (i == 11)
                    {
                        passwordEntered = true;
                        if (strcmp(password, correctPassword) == 0)
                        {
                            passwordCorrect = true;
                            
                        }
                        else
                        {
                            passwordCorrect = false;
                        }
                    }
                }
                else
                {
                    if (passLength < MAX_PASS)
                    {
                        password[passLength++] = '0' + keypad[i].value;
                        password[passLength] = '\0';
                    }
                }
            }
        }
    }
}

void DrawKeypad()
{
    DrawRectangleRec(closeButton, MAROON);
    DrawRectangleLinesEx(closeButton, 2, WHITE);

    DrawText(
        "X",
        closeButton.x + 8,
        closeButton.y + 4,
        20,
        WHITE
    );
    
    for (int i = 0; i < 9; i++)
    {
        int row = i / 3;
        int col = i % 3;

        keypad[i].bounds = (Rectangle){
            startXkeypad + col * (size + gap),
            startYkeypad + row * (size + gap),
            size,
            size
        };

        keypad[i].value = numbers[i];
    }

    // tombol 0
    keypad[9].bounds = (Rectangle){
        startXkeypad + size + gap,
        startYkeypad + 3 * (size + gap),
        size,
        size
    };
    keypad[9].value = 0;
    
    // tombol delete
    keypad[10].bounds = (Rectangle){
        startXkeypad,
        startYkeypad + 3 * (size + gap),
        size,
        size
    };
    keypad[10].value = 'x';
    
    // tombol enter
    keypad[11].bounds = (Rectangle){
        startXkeypad + 2 * (size + gap),
        startYkeypad + 3 * (size + gap),
        size,
        size
    };
    keypad[11].value = 'o';
    
    for (int i = 0; i < 12; i++)
    {
        DrawRectangleRec(keypad[i].bounds, DARKGRAY);
        DrawRectangleLinesEx(keypad[i].bounds, 2, WHITE);

        char num[2];
        
        if (i > 9)
        {
            num[0] = keypad[i].value;
            num[1] = '\0';
        }
        else
        {
            sprintf(num, "%d", keypad[i].value);
        }

        DrawText(
            num,
            keypad[i].bounds.x + 25,
            keypad[i].bounds.y + 20,
            30,
            WHITE
        );
    }
    DrawRectangleRec((Rectangle){startXkeypad, startYkeypad - (size + 10), 3 * (size + gap), 60}, DARKGRAY);
    DrawRectangleLinesEx((Rectangle){startXkeypad, startYkeypad - (size + 10), 3 * (size + gap), 60}, 3, WHITE);    
    DrawText(password, startXkeypad + 10, startYkeypad - (size), 40, WHITE);
    
    if (passwordEntered && passwordCorrect)
    {
        DrawText("Correct", startXkeypad + 4 * (size + gap), startYkeypad - (size + gap), 40, GREEN);
    }
    else if (passwordEntered && !passwordCorrect)
    {
        DrawText("False", startXkeypad + 4 * (size + gap), startYkeypad - (size + gap), 40, RED);
    }
}*/


void UnloadPuzzle1FutureScene()
{

}