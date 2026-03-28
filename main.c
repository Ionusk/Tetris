#include "raylib.h"
#include "input.h"
#include "measure.h"

int main(void)
{
    int screenWidth = 800;
    int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Tetris");
    SetTargetFPS(60);

    // Blocul curent (pătrat simplu)
    int blockX = PLAY_X + (COLS / 2) * CELL_SIZE;
    int blockY = PLAY_Y;

    Input input = {0};

    while (!WindowShouldClose())
    {
        // --- INPUT ---
        UpdateInput(&input);

        // Mutare bloc ținând cont de limitele zonei de joc
        if (input.left && blockX > PLAY_X)
            blockX -= CELL_SIZE;
        if (input.right && blockX < PLAY_X + PLAY_WIDTH - CELL_SIZE)
            blockX += CELL_SIZE;
        if (input.down && blockY < PLAY_Y + PLAY_HEIGHT - CELL_SIZE)
            blockY += CELL_SIZE;
        if (input.rotate)
        {
            // aici poți implementa rotirea blocului
        }

        // --- DESENARE ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Titlu centrat sus
        const char* title = "TETRIS";
        int fontSize = 40;
        int textWidth = MeasureText(title, fontSize);
        DrawText(title, (screenWidth - textWidth) / 2, 20, fontSize, BLACK);

        // Zona de joc (dreptunghi roșu)
        DrawRectangle(PLAY_X, PLAY_Y, PLAY_WIDTH, PLAY_HEIGHT, RED);

        // Blocul curent (albastru)
        DrawRectangle(blockX, blockY, CELL_SIZE, CELL_SIZE, BLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}