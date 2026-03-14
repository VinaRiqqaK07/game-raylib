#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include "puzzle1_scene.h"
#include "../utils/constants.h"
#include "../core/game.h"
#include "../core/scene_manager.h"
#include "../systems/ui_system.h"

#define MAX_PASS 8

char password[MAX_PASS+1] = "\0";
int passLength = 0;


typedef struct {
    Rectangle bounds;
    int value;
} KeypadButton;

KeypadButton keypad[12];

int startXkeypad = 300;
int startYkeypad = 250;
int size = 70;
int gap = 10;

int numbers[10] = {1,2,3,4,5,6,7,8,9,0};
const char correctPassword[] = "5431";
bool passwordEntered = false;
bool passwordCorrect = false;

typedef struct PuzzleBox
{
    Vector2 position;
    float rotation;
    bool flipped;

} PuzzleBox;

PuzzleBox box;
Vector2 center;

char digit;
bool numberOne, numberTwo, numberThree;

void InitPuzzle1Scene()
{
    box.position = (Vector2){400, 300};
    box.rotation = 0;
    box.flipped = false;
    
}

void UpdatePuzzle1Scene()
{
    if (game.role == ROLE_PAST)
    {
        UpdatePuzzle1Past();
    }
    else if (game.role == ROLE_FUTURE)
    {
        UpdatePuzzle1Future();
    }
}

void UpdatePuzzle1Past()
{
    Rectangle boxRect = {box.position.x - 120, box.position.y - 120, 360, 360};
    
    if (CheckCollisionPointRec(GetMousePosition(), boxRect))
    {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            float mouseDelta = GetMouseDelta().x;
            box.rotation += mouseDelta * 0.5f;
            DrawText("Mouse Left Down", 500, 600, 20, WHITE);
        }
        
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            box.flipped = !box.flipped;
        }
        
    }
}

void UpdatePuzzle1Future()
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


void DrawPuzzle1Scene()
{
    ClearBackground(BLACK);
    
    
    
    if (game.role == ROLE_PAST)
    {
        DrawPuzzle1Past();
    }
    else if (game.role == ROLE_FUTURE)
    {
        DrawPuzzle1Future();
    }
    
    
}

void DrawPuzzle1Past()
{
    //DrawText("PAST PUZZLE LEVEL 1", 300, SCREEN_HEIGHT/2, 20, WHITE);
    
    // RECTANGLE ROTATION
    Vector2 origin = {60, 60};

    float width = 120;
    
    Rectangle drawRect = {box.position.x, box.position.y, width, 120};
    
    if(box.flipped)
        DrawRectanglePro(
            drawRect,
            origin,
            box.rotation,
            BLUE
        );
    else 
        DrawRectanglePro(
            drawRect,
            origin,
            box.rotation,
            RED
        );
    
    center = box.position;
    
}

void DrawPuzzle1Future()
{
    DrawText("FUTURE PUZZLE LEVEL 1", 100, 20, 20, WHITE);
    
    DrawKeypad();
    
    if (passwordEntered && passwordCorrect)
    {
        DrawText("Correct", 450, 180, 40, GREEN);
    }
    else if (passwordEntered && !passwordCorrect)
    {
        DrawText("False", 450, 180, 40, RED);
    }
}

void DrawKeypad()
{
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
    DrawText(password, 340, 180, 40, WHITE);
    
}


void UnloadPuzzle1Scene()
{

}