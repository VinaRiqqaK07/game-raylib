#include "raylib.h"
#include "../utils/constants.h"
#include "../core/scene_manager.h"
#include "../core/game.h"
#include <string.h>

char inputText[64] = "\0";
int letterCount = 0;

bool isTyping = false;
bool submitted = false;
bool inputCorrect = false;
bool isInputMoments = true;

Rectangle inputBox = {SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2, 300, 40};
Rectangle submitBtn = {SCREEN_WIDTH/2 - 60, SCREEN_HEIGHT/2 + 60, 120, 40};

void InitMoments(bool isMoments)
{
    inputCorrect = false;
    isInputMoments = isMoments;
    letterCount = 0;
    inputText[0] = '\0';
    isTyping = false;
    submitted = false;
}

void UpdateMoments()
{
    Vector2 mouse = GetMousePosition();

    // klik input box
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        isTyping = CheckCollisionPointRec(mouse, inputBox);
    }

    // ================= TEXT INPUT =================
    if (isTyping && !submitted)
    {
        int key = GetCharPressed();

        while (key > 0)
        {
            // hanya huruf kecil
            if ((key >= 'a') && (key <= 'z') && letterCount < 63)
            {
                inputText[letterCount] = (char)key;
                letterCount++;
                inputText[letterCount] = '\0';
            }

            key = GetCharPressed();
        }

        // backspace
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            if (letterCount > 0)
            {
                letterCount--;
                inputText[letterCount] = '\0';
            }
        }
    }

    // ================= SUBMIT =================

    // klik tombol
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(mouse, submitBtn) &&
        letterCount > 0)
    {
        submitted = true;
    }

    // tekan enter
    if ((IsKeyPressed(KEY_ENTER) || submitted == true) && letterCount > 0)
    {
        if (isInputMoments && game.role == ROLE_PAST)
        {
            if (strcmp(inputText, "moments") == 0)
            {
                submitted = true;
                inputCorrect = true;
            }
            else
            {
                inputCorrect = false;

                // reset biar player coba lagi
                letterCount = 0;
                inputText[0] = '\0';
            }
        }
        else if (!isInputMoments && game.role == ROLE_PAST)
        {
            if (strcmp(inputText, "failed") == 0)
            {
                submitted = true;
                inputCorrect = true;
            }
            else
            {
                inputCorrect = false;

                // reset biar player coba lagi
                letterCount = 0;
                inputText[0] = '\0';
            }
        }
        else if (game.role == ROLE_FUTURE)
        {
            if (strcmp(inputText, "moments") == 0 || strcmp(inputText, "failed") == 0)
            {
                submitted = true;
                inputCorrect = true;
            }
            else
            {
                inputCorrect = false;

                // reset biar player coba lagi
                letterCount = 0;
                inputText[0] = '\0';
            }
        }
        
    }

    // pindah scene kalau sudah submit
    if (submitted && inputCorrect)
    {
        if (strcmp(inputText, "moments") == 0)
        {
            ChangeScene(SCENE_ENDING);
        }
        else
        {
            ChangeScene(SCENE_PUZZLE1);
        }
        
    }
}

void DrawMoments()
{
    // ===== BACKGROUND DARKEN =====
    //DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.6f));

    // ===== TITLE =====
    if (game.role == ROLE_PAST)
    {
        if (isInputMoments)
        {
            DrawText("Type 'moments' for both players.", SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 - 80, 30, WHITE);
        }
        else 
        {
             DrawText("Type 'failed' for both players.", SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 - 80, 30, WHITE);
        }
    }
    
    

    // ===== INPUT BOX =====
    DrawRectangleRec(inputBox, DARKGRAY);
    DrawRectangleLinesEx(inputBox, 2, isTyping ? YELLOW : LIGHTGRAY);

    // text
    DrawText(inputText, inputBox.x + 10, inputBox.y + 10, 20, WHITE);

    // cursor blinking
    if (isTyping && ((int)(GetTime()*2) % 2))
    {
        DrawText("|", inputBox.x + 10 + MeasureText(inputText, 20), inputBox.y + 10, 20, WHITE);
    }

    // ===== SUBMIT BUTTON =====
    DrawRectangleRec(submitBtn, GRAY);
    DrawRectangleLinesEx(submitBtn, 2, WHITE);

    DrawText("Submit",
        submitBtn.x + 20,
        submitBtn.y + 10,
        20,
        WHITE
    );
}