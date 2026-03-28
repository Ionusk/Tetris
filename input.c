#include "input.h"
#include "raylib.h"

// Actualizează input-ul de la tastatură
void UpdateInput(Input* input)
{
    if (!input) return;

    input->left   = IsKeyDown(KEY_LEFT);
    input->right  = IsKeyDown(KEY_RIGHT);
    input->down   = IsKeyDown(KEY_DOWN);
    input->rotate = IsKeyPressed(KEY_UP); // rotire doar la apăsare
}