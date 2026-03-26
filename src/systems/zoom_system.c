/**
 * Zoom System
 *
 * Displays and handle Logic for interactable environment. 
 * When some area is clicked, zoom animation is rendered to show the detailed texture.
 *
 * Usage:
 * 1. Call InitZoomSystem() once
 * 2. Call TriggerZoom() with the detailed texture when an area of interact is clicked
 * 3. Call UpdateZoomSystem() every frame
 * 4. Call DrawZoomSystem() in render loop 
 *
 */

#include "raylib.h"
#include <math.h>
#include "../utils/constants.h"

/**
 * Iterable zoom state
 */
typedef enum {
    ZOOM_IDLE,
    ZOOM_IN,
    ZOOMED,
    ZOOM_OUT
} ZoomState;

/**
 * Represents zoom system and every item needed to handle logic, state, and render
 */
typedef struct {
    Texture2D texMain;      // Main texture rendered for a screen
    Texture2D texDetail;    // Detailed texture for zoomed interact

    Texture2D currentTex;   // Current texture rendered 

    float zoom;             // Current zoom state (1.0 → normal)
    float targetZoom;       // Target zoom for animation (1.0 < atau 2.0)

    bool switched;          // Is texture has been switched from main to detail

    ZoomState state;        // Current zoom state

    Rectangle backButton;   // Back button from detailed texture to main texture
} ZoomSystem;

void InitZoomSystem(ZoomSystem *z, Texture2D mainTex)
{
    z->texMain = mainTex;
    z->currentTex = mainTex;

    z->zoom = 1.0f;
    z->targetZoom = 1.0f;

    z->state = ZOOM_IDLE;
    z->switched = false;

    z->backButton = (Rectangle){20, 20, 100, 40};
}

void TriggerZoom(ZoomSystem *z, Texture2D detailTex)
{
    if (z->state != ZOOM_IDLE) return;

    z->texDetail = detailTex;
    z->targetZoom = 2.5f;   // zoom in
    z->state = ZOOM_IN;
    z->switched = false;
}

void UpdateZoomSystem(ZoomSystem *z)
{
    // smooth zoom
    z->zoom += (z->targetZoom - z->zoom) * 0.1f;

    // ZOOM IN
    if (z->state == ZOOM_IN)
    {
        if (!z->switched && z->zoom > 2.3f)
        {
            z->currentTex = z->texDetail;
            z->switched = true;
            z->zoom = 1.0f;
            z->targetZoom = 1.0f;
        }

        if (fabs(z->zoom - z->targetZoom) < 0.01f)
        {
            z->state = ZOOMED;
        }
    }

    // ZOOMED → tunggu back
    if (z->state == ZOOMED)
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(GetMousePosition(), z->backButton))
            {
                z->zoom = 1.0f;
                z->targetZoom = 1.0f;
                z->state = ZOOM_OUT;
                z->switched = false;
            }
        }
    }

    // ZOOM OUT
    if (z->state == ZOOM_OUT)
    {
        if (!z->switched && z->zoom < 1.2f)
        {
            z->currentTex = z->texMain;
            z->switched = true;
            z->zoom = 2.5f;
            z->targetZoom = 1.0f;
        }

        if (fabs(z->zoom - z->targetZoom) < 0.01f)
        {
            z->state = ZOOM_IDLE;
        }
    }
}

void DrawZoomSystem(ZoomSystem *z)
{
    Texture2D currentTex = z->currentTex;
    
    /*
    if (z->state == ZOOM_IDLE || z->state == ZOOM_IN)
        currentTex = z->texMain;
    else
        currentTex = z->texDetail;
    */
    // 🔥 Hitung zoom ke source (bukan dest)
    float zoom = z->zoom;

    float srcWidth = currentTex.width / zoom;
    float srcHeight = currentTex.height / zoom;

    Rectangle source = {
        (currentTex.width - srcWidth) / 2,
        (currentTex.height - srcHeight) / 2,
        srcWidth,
        srcHeight
    };

    // Dest selalu fullscreen
    Rectangle dest = {
        0,
        0,
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    };

    DrawTexturePro(
        currentTex,
        source,
        dest,
        (Vector2){0,0},
        0.0f,
        WHITE
    );

    // Tombol back
    if (z->state == ZOOMED)
    {
        DrawRectangleRec(z->backButton, DARKGRAY);
        DrawText("BACK", z->backButton.x + 10, z->backButton.y + 10, 20, WHITE);
    }
}


