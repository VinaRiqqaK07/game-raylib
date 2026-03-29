/**
 * Keypad System 2
 *
 * Displays and handle Logic for keypad such as keyboard and mouse input, keypad popup, and checking password.
 *
 * Usage:
 * 1. Call InitKeypad2() once with initialized Keypad Pointer (correct password, maxLength, and panel)
 * 2. Call UpdateKeypad2() every frame
 * 3. Call DrawKeypad2() in render loop with if statement keypad rendered fully
 *
 *
 * Note
 * - This file contains the same code as keypad_system.c but with no comments for general purposes
 */

#include "raylib.h"
#include <stdio.h>
#include <string.h>

/**
 * Represents each keypad button, consists of its value/text on the button and its area
 */
typedef struct {
    Rectangle bounds;
    int value;
} KeypadButton2;

/**
 * Represents an interactive keypad with its logic and render item
 */
typedef struct {
    char password[10];          // Password inputted
    int passLength;             // Current Length of inputted password
    int maxLength;              // Max Length of password

    bool isOpen;                // Is keypad opened
    bool opening;               // Is keypad in open transition
    
    int startXkeypad;           // X coordinate where the keypad start
    int startYkeypad;           // Y coordinate where the keypad start
    int size;                   // Size of each button
    int gap;                    // Gap for each item

    Rectangle panel;            // Keypad panel
    Rectangle target;           // Target position for keypad panel
    Rectangle start;            // Start position of keypad panel
    Rectangle closeButton;      // Close button of keypad
    KeypadButton2 button[12];    // All button in keypad

    bool passwordEntered;       // Is password entered
    bool passwordCorrect;       // Is password correct

    const char *correctPassword; //Correct password
} Keypad2;


// Numbers in keypad
int numbers2[10] = {1,2,3,4,5,6,7,8,9,0};

void InitKeypad2(Keypad2 *kp)
{
    kp->passLength = 0;
    kp->password[0] = '\0';

    kp->opening = false;
    kp->isOpen = false;
    
    kp->startXkeypad = 300;
    kp->startYkeypad = 250;
    kp->size = 70;
    kp->gap = 10;

    //kp->panel = (Rectangle){140, 345, 78, 100}; // INI JI NANTI DIHAPUS
    kp->target = (Rectangle){300, 250, 240, 320};
    kp->start = kp->panel;

    kp->closeButton = (Rectangle){
        kp->startXkeypad + kp->target.width - 30,
        kp->startYkeypad -(kp->size + 50),
        30, 30
    };
}

void HandleUpdateKeypad2(Keypad2 *kp)
{
    // Keyboard keypad input
    int key = GetKeyPressed();

    if (key >= KEY_ZERO && key <= KEY_NINE)
    {
        if (kp->passLength < kp->maxLength)
        {
            kp->password[kp->passLength++] = '0' + (key - KEY_ZERO);
            kp->password[kp->passLength] = '\0';
        }
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        kp->passLength--;
        if (kp->passLength < 0) kp->passLength = 0;
        kp->password[kp->passLength] = '\0';
        kp->passwordEntered = false;
    }
    
    //Mouse keypad input
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        for (int i = 0; i < 12; i++)
        {
            if (CheckCollisionPointRec(mouse, kp->button[i].bounds))
            {
                if (i > 9)
                {
                    if (i == 10)
                    {
                        kp->passLength = 0;
                        if (kp->passLength < 0) kp->passLength = 0;
                        kp->password[kp->passLength] = '\0';
                        kp->passwordEntered = false;
                    }
                    if (i == 11)
                    {
                        kp->passwordEntered = true;
                        if (strcmp(kp->password, kp->correctPassword) == 0 || kp->passwordCorrect == true)
                        {
                            kp->passwordCorrect = true;
                            
                        }
                        else
                        {
                            kp->passwordCorrect = false;
                        }
                    }
                }
                else
                {
                    if (kp->passLength < kp->maxLength)
                    {
                        kp->password[kp->passLength++] = '0' + kp->button[i].value;
                        kp->password[kp->passLength] = '\0';
                    }
                }
            }
        }
    }
}

void UpdateKeypad2(Keypad2 *kp)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(GetMousePosition(), kp->panel) && !kp->passwordCorrect)
        {
            kp->opening = true;
            kp->isOpen = true;
        }
        else if (CheckCollisionPointRec(GetMousePosition(), kp->closeButton))
        {
            kp->opening = false; 
            kp->isOpen = false; // atau state kamu untuk menutup
        }
    }
        
    
    
    if (kp->opening)
    {
        kp->panel.x += (kp->target.x - kp->panel.x) * 0.1f;
        kp->panel.y += (kp->target.y - kp->panel.y) * 0.1f;
        kp->panel.width += (kp->target.width - kp->panel.width) * 0.1f;
        kp->panel.height += (kp->target.height - kp->panel.height) * 0.1f;
    }
    else
    {
        kp->panel.x += (kp->start.x - kp->panel.x) * 0.1f;
        kp->panel.y += (kp->start.y - kp->panel.y) * 0.1f;
        kp->panel.width += (kp->start.width - kp->panel.width) * 0.1f;
        kp->panel.height += (kp->start.height - kp->panel.height) * 0.1f;
    }
    
    if (kp->panel.width > 200 && kp->opening)
    {
        kp->isOpen = true;
        HandleUpdateKeypad2(kp); 
    }
    else
    {
        kp->isOpen = false;
    }
}

void DrawKeypad2(Keypad2 *kp)
{
    DrawRectangleRec(kp->closeButton, MAROON);
    DrawRectangleLinesEx(kp->closeButton, 2, WHITE);

    DrawText(
        "X",
        kp->closeButton.x + 8,
        kp->closeButton.y + 4,
        20,
        WHITE
    );
    
    for (int i = 0; i < 9; i++)
    {
        int row = i / 3;
        int col = i % 3;

        kp->button[i].bounds = (Rectangle){
            kp->startXkeypad + col * (kp->size + kp->gap),
            kp->startYkeypad + row * (kp->size + kp->gap),
            kp->size,
            kp->size
        };

        kp->button[i].value = numbers2[i];
    }

    // tombol 0
    kp->button[9].bounds = (Rectangle){
        kp->startXkeypad + kp->size + kp->gap,
        kp->startYkeypad + 3 * (kp->size + kp->gap),
        kp->size,
        kp->size
    };
    kp->button[9].value = 0;
    
    // tombol delete
    kp->button[10].bounds = (Rectangle){
        kp->startXkeypad,
        kp->startYkeypad + 3 * (kp->size + kp->gap),
        kp->size,
        kp->size
    };
    kp->button[10].value = 'x';
    
    // tombol enter
    kp->button[11].bounds = (Rectangle){
        kp->startXkeypad + 2 * (kp->size + kp->gap),
        kp->startYkeypad + 3 * (kp->size + kp->gap),
        kp->size,
        kp->size
    };
    kp->button[11].value = 'v';
    
    for (int i = 0; i < 12; i++)
    {
        DrawRectangleRec(kp->button[i].bounds, DARKGRAY);
        DrawRectangleLinesEx(kp->button[i].bounds, 2, WHITE);

        char num[2];
        
        if (i > 9)
        {
            num[0] = kp->button[i].value;
            num[1] = '\0';
        }
        else
        {
            sprintf(num, "%d", kp->button[i].value);
        }

        DrawText(
            num,
            kp->button[i].bounds.x + 25,
            kp->button[i].bounds.y + 20,
            30,
            WHITE
        );
    }
    DrawRectangleRec((Rectangle){kp->startXkeypad, kp->startYkeypad - (kp->size + 10), 3 * (kp->size + kp->gap), 60}, DARKGRAY);
    DrawRectangleLinesEx((Rectangle){kp->startXkeypad, kp->startYkeypad - (kp->size + 10), 3 * (kp->size + kp->gap), 60}, 3, WHITE);    
    DrawText(kp->password, kp->startXkeypad + 10, kp->startYkeypad - (kp->size), 40, WHITE);
    
    if (kp->passwordEntered && kp->passwordCorrect)
    {
        DrawText("Correct", kp->startXkeypad + 4 * (kp->size + kp->gap), kp->startYkeypad - (kp->size + kp->gap), 40, GREEN);
    }
    else if (kp->passwordEntered && !(kp->passwordCorrect))
    {
        DrawText("False", kp->startXkeypad + 4 * (kp->size + kp->gap), kp->startYkeypad - (kp->size + kp->gap), 40, RED);
    }
    
}
