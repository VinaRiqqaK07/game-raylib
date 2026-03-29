#include "raylib.h"
#include "../utils/constants.h"
#include "../core/scene_manager.h"
#include <string.h>

char inputText[64] = "\0";
int letterCount = 0;

bool isTyping = false;
bool submitted = false;
bool inputCorrect = false;

Rectangle inputBox = {SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2, 300, 40};
Rectangle submitBtn = {SCREEN_WIDTH/2 - 60, SCREEN_HEIGHT/2 + 60, 120, 40};

void InitMoments(Rectangle input, Rectangle submit)
{
    inputBox = input;
    submitBtn = submit;
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

    // pindah scene kalau sudah submit
    if (submitted && inputCorrect)
    {
        ChangeScene(SCENE_ENDING);
    }
}

void DrawMoments()
{
    // ===== BACKGROUND DARKEN =====
    //DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.6f));

    // ===== TITLE =====
    DrawText("Type 'moments' to end this.", SCREEN_WIDTH/2 - 80, SCREEN_HEIGHT/2 - 80, 30, WHITE);

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