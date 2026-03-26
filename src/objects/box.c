/**
 * File: box.c
 * Description:
 * Handles the logic and rendering for interactable object (drag, rotate, flip).
 *
 * Usage : 
 * 1. Call UpdateBox() every frame
 * 2. Call DrawBox() in render loop
 *
 * Dependencies:
 * - math.h (for rotation function)
 *
 */

#include "raylib.h"
#include <math.h>


/**
* Represents an interactive draggable object.
* Supports rotation, flipping, and drag mechanics.
*/
typedef struct {
    Vector2 position;           // Current position on screen
    float targetWidth;          // Render size (scaled width)
    float rotation;             // Rotation angle in degrees
    bool flipped;               // Whether texture is flipped or not

    bool dragging;              // Is currently being dragged
    bool rotating;              // Is currently being rotated
    Vector2 dragOffset;         // Offset between mouse and object center for drag
    
    Texture2D textureTop;       // Texture rendered when not flipped
    Texture2D textureBottom;    // Texture rendered when flipped
} Box;

float widthBox, heightBox;
float margin = 50;

/**
 * Updates the interaction logic for a Box.
 *
 * Handles:
 * - Dragging (inside inner hitbox)
 * - Rotation (outside inner but inside outer hitbox)
 * - Flipping (right click)
 *
 * @param box Pointer to the Box object to update
 *
 * Behavior:
 * - Left click inside inner area → drag
 * - Left click outside → rotate
 * - Right click → flip texture
 */
void UpdateBox(Box *box)
{
    Rectangle inner = {
        box->position.x - 50,
        box->position.y - 50,
        280,
        280
    };
    Rectangle outer = {
        box->position.x - 120,
        box->position.y - 120,
        420,
        420
    };

   Vector2 mouse = GetMousePosition();

    // START INPUT
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mouse, inner))
        {
            // DRAG MODE
            box->dragging = true;
            box->rotating = false;

            box->dragOffset.x = mouse.x - box->position.x;
            box->dragOffset.y = mouse.y - box->position.y;
        }
        else if (CheckCollisionPointRec(mouse, outer))
        {
            // ROTATE MODE
            box->rotating = true;
            box->dragging = false;
        }
    }
    else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
    {
        if (CheckCollisionPointRec(mouse, inner))
        {
            box->flipped = !box->flipped;
        }
    }
    
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        box->dragging = false;
        box->rotating = false;
    }
    
    if (box->dragging)
    {
        box->position.x = mouse.x - box->dragOffset.x;
        box->position.y = mouse.y - box->dragOffset.y;
    }
    
    if (box->rotating)
    {
        Vector2 dir = {
            mouse.x - box->position.x,
            mouse.y - box->position.y
        };

        float angle = atan2f(dir.y, dir.x) * RAD2DEG;
        box->rotation = angle;
    }
}

/**
 * Draw/Render Item.
 *
 * 
 * @param box Pointer to the Box object to draw
 *
 * Responsibilities :
 * - Render selected texture based on item state (flipped or not)
 * - Scale item height based on width target.
 * - Draw texture using DrawTexturePro().
 */
void DrawBox(Box *box)
{
    Texture2D tex = box->flipped ? box->textureBottom : box->textureTop;
    
    float widthBox = box->targetWidth;
    float ratio = (float)tex.height / tex.width;

    float heightBox = box->targetWidth * ratio;

    Rectangle source = {
        0,
        0,
        tex.width,
        tex.height
    };

    Vector2 origin = {box->targetWidth/2, heightBox/2};

    Rectangle dest = {
        box->position.x,
        box->position.y,
        widthBox,
        heightBox
    };

    DrawTexturePro(tex,source,dest,origin,box->rotation,WHITE);
    
    // Debugging Text
    //DrawText(TextFormat("X: %.0f Y: %.0f", box->position.x, box->position.y),box->position.x,box->position.y - 100,20,WHITE);
}

