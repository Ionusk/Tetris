#include "input.h"
#include "raylib.h"

void UpdateInput(Input* input)
{
    if (!input) return;

    input->left   = IsKeyPressed(KEY_LEFT);
    input->right  = IsKeyPressed(KEY_RIGHT);
    input->down   = IsKeyDown(KEY_DOWN);
    input->rotate = IsKeyPressed(KEY_UP);
}