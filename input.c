#include "input.h"
#include "raylib.h"

#define HOLD_DELAY 0.2f
#define REPEAT_RATE 0.05f

void UpdateInput(Input* input)
{
    if (!input) return;

    float dt = GetFrameTime();

    input->left  = false;
    input->right = false;

    if (IsKeyPressed(KEY_LEFT))
    {
        input->left = true;
        input->leftHold = 0;
    }
    else if (IsKeyDown(KEY_LEFT))
    {
        input->leftHold += dt;
        if (input->leftHold >= HOLD_DELAY)
        {
            input->left = true;
            input->leftHold -= REPEAT_RATE;
        }
    }
    else
    {
        input->leftHold = 0;
    }

    if (IsKeyPressed(KEY_RIGHT))
    {
        input->right = true;
        input->rightHold = 0;
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        input->rightHold += dt;
        if (input->rightHold >= HOLD_DELAY)
        {
            input->right = true;
            input->rightHold -= REPEAT_RATE;
        }
    }
    else
    {
        input->rightHold = 0;
    }

    input->down = IsKeyDown(KEY_DOWN);
    
  
    input->rotate = IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_SPACE);
}