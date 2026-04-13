#include "screen.h"



int CanMove(int newX, int newY)
{
    int col = (newX - PLAY_X) / CELL_SIZE;
    int row = (newY - PLAY_Y) / CELL_SIZE;

    int cells[4][2] = {
        {col, row},
        {col+1, row},
        {col, row+1},
        {col+1, row+1}
    };

    for (int i = 0; i < 4; i++)
    {
        int c = cells[i][0];
        int r = cells[i][1];

        if (c < 0 || c >= COLOANE || r < 0 || r >= RANDURI)
            return 0;

        if (grid[r][c])
            return 0;
    }

    return 1;
}


// ======================================================
// 🔥 LOCK PIECE INTO GRID
// ======================================================
void LockPiece()
{
    int col = (blockX - PLAY_X) / CELL_SIZE;
    int row = (blockY - PLAY_Y) / CELL_SIZE;

    grid[row][col] = 1;
    grid[row][col + 1] = 1;
    grid[row + 1][col] = 1;
    grid[row + 1][col + 1] = 1;
}


// ======================================================
// 🔥 SPAWN PIECE
// ======================================================
void SpawnPiece()
{
    blockX = PLAY_X + (COLOANE / 2) * CELL_SIZE;
    blockY = PLAY_Y;
}


// ======================================================
// INIT
// ======================================================
void ScreenInit()
{
    state = MENU;
    startButton = (Rectangle){300, 200, 200, 60};

    SpawnPiece();
}


// ======================================================
// UPDATE
// ======================================================
void ScreenUpdate()
{
    Vector2 mouse = GetMousePosition();

    // ================= MENU =================
    if (state == MENU)
    {
        if (CheckCollisionPointRec(mouse, startButton) &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            state = GAME;
            SpawnPiece();
        }
        return;
    }

    // ================= GAME =================
    UpdateInput(&input);

    // ================= LEFT =================
    if (input.left)
    {
        if (CanMove(blockX - CELL_SIZE, blockY))
            blockX -= CELL_SIZE;
    }

    // ================= RIGHT =================
    if (input.right)
    {
        if (CanMove(blockX + CELL_SIZE, blockY))
            blockX += CELL_SIZE;
    }

    // ================= DOWN (manual drop) =================
    if (input.down)
    {
        if (CanMove(blockX, blockY + CELL_SIZE))
            blockY += CELL_SIZE;
    }

    // ================= GRAVITY =================
    fallTimer += GetFrameTime();

    if (fallTimer >= fallSpeed)
    {
        if (CanMove(blockX, blockY + CELL_SIZE))
        {
            blockY += CELL_SIZE;
        }
        else
        {
            LockPiece();
            SpawnPiece();
        }

        fallTimer = 0;
    }
}


// ======================================================
// DRAW
// ======================================================
void ScreenDraw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (state == MENU)
    {
        DrawText("TETRIS", 320, 100, 40, BLACK);

        DrawRectangleRec(startButton, GRAY);
        DrawText("START GAME", 330, 220, 20, BLACK);
    }
    else
    {
        // 🔥 PLAYFIELD (mov, mare, centrat)
        DrawRectangle(PLAY_X, PLAY_Y, PLAY_WIDTH, PLAY_HEIGHT, PURPLE);

        // ================= GRID BLOCKS =================
        for (int r = 0; r < RANDURI; r++)
        {
            for (int c = 0; c < COLOANE; c++)
            {
                if (grid[r][c])
                {
                    DrawRectangle(
                        PLAY_X + c * CELL_SIZE,
                        PLAY_Y + r * CELL_SIZE,
                        CELL_SIZE,
                        CELL_SIZE,
                        BLUE
                    );
                }
            }
        }

        // ================= CURRENT PIECE (2x2) =================
        DrawRectangle(blockX, blockY, CELL_SIZE, CELL_SIZE, PINK);
        DrawRectangle(blockX + CELL_SIZE, blockY, CELL_SIZE, CELL_SIZE, PINK);
        DrawRectangle(blockX, blockY + CELL_SIZE, CELL_SIZE, CELL_SIZE, PINK);
        DrawRectangle(blockX + CELL_SIZE, blockY + CELL_SIZE, CELL_SIZE, CELL_SIZE, PINK);
    }

    EndDrawing();
}