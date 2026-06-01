#include "screen.h"
#include "measure.h"
#include <stdlib.h>
#include <time.h>

// ================= STATE =================

static GameState state;
static Rectangle startButton;
static Input input;

static int grid[LINII][COLOANE];
static int blockX;
static int blockY;

static float fallTimer = 0;
static float fallSpeed = 0.4f;

// ================= PIESE =================

static int pieces[7][4][4] = {

    // O
    {
        {1,1,0,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    },

    // I
    {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    },

    // T
    {
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },

    // L
    {
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },

    // J
    {
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },

    // S
    {
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    },

    // Z
    {
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    }
};

static int currentPiece[4][4];
static int pieceType;

// ================= INIT =================

void ScreenInit()
{
    state = MENU;
    startButton = (Rectangle){300, 200, 200, 60};

    srand(time(NULL));

    // clear grid
    for (int r = 0; r < LINII; r++)
        for (int c = 0; c < COLOANE; c++)
            grid[r][c] = 0;
}

// ================= SPAWN =================

void SpawnPiece()
{
    pieceType = rand() % 7;

    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            currentPiece[r][c] = pieces[pieceType][r][c];

    blockX = PLAY_X + (COLOANE / 2) * CELL_SIZE;
    blockY = PLAY_Y;
}

// ================= CAN MOVE =================

int CanMove(int newX, int newY)
{
    int col0 = (newX - PLAY_X) / CELL_SIZE;
    int row0 = (newY - PLAY_Y) / CELL_SIZE;

    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 4; c++)
        {
            if (!currentPiece[r][c])
                continue;

            int col = col0 + c;
            int row = row0 + r;

            if (col < 0 || col >= COLOANE || row < 0 || row >= LINII)
                return 0;

            if (grid[row][col])
                return 0;
        }
    }

    return 1;
}

// ================= LOCK PIECE (SAFE) =================

void LockPiece()
{
    int col0 = (blockX - PLAY_X) / CELL_SIZE;
    int row0 = (blockY - PLAY_Y) / CELL_SIZE;

    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 4; c++)
        {
            if (!currentPiece[r][c])
                continue;

            int row = row0 + r;
            int col = col0 + c;

            if (row < 0 || row >= LINII || col < 0 || col >= COLOANE)
                continue;

            grid[row][col] = 1;
        }
    }
}

// ================= UPDATE =================

void ScreenUpdate()
{
    Vector2 mouse = GetMousePosition();

    if (state == MENU)
    {
        if (CheckCollisionPointRec(mouse, startButton) &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            state = GAME;

            // reset grid
            for (int r = 0; r < LINII; r++)
                for (int c = 0; c < COLOANE; c++)
                    grid[r][c] = 0;

            SpawnPiece();
        }
        return;
    }

    UpdateInput(&input);

    if (input.left && CanMove(blockX - CELL_SIZE, blockY))
        blockX -= CELL_SIZE;

    if (input.right && CanMove(blockX + CELL_SIZE, blockY))
        blockX += CELL_SIZE;

    if (input.down && CanMove(blockX, blockY + CELL_SIZE))
        blockY += CELL_SIZE;

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

// ================= DRAW =================

void ScreenDraw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (state == MENU)
    {
        DrawText("TETRIS", 320, 100, 40, BLACK);
        DrawRectangleRec(startButton, GRAY);
        DrawText("START GAME", 330, 220, 20, BLACK);
        EndDrawing();
        return;
    }

    DrawRectangle(PLAY_X, PLAY_Y, PLAY_WIDTH, PLAY_HEIGHT, PURPLE);

    // grid
    for (int r = 0; r < LINII; r++)
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
                    YELLOW
                );
            }
        }
    }

    // piece
    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 4; c++)
        {
            if (currentPiece[r][c])
            {
                DrawRectangle(
                    blockX + c * CELL_SIZE,
                    blockY + r * CELL_SIZE,
                    CELL_SIZE,
                    CELL_SIZE,
                    PINK
                );
            }
        }
    }

    EndDrawing();
}