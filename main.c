#include "raylib.h"
#include "input.h"
#include "screen.h"
#include "measure.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Tetris");
    SetTargetFPS(60);

    ScreenInit();
    SetExitKey(KEY_Q);
    while (!WindowShouldClose())
    {
        ScreenUpdate();
        ScreenDraw();
    }

    CloseWindow();
    return 0;
}