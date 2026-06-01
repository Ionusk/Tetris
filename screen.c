#include "screen.h"
#include "measure.h"
#include <stdlib.h>
#include <time.h>


void ScreenInit()
{
    state = MENU;
    startButton = (Rectangle){350, 250, 200, 60};
    srand(time(NULL));

    for (int r = 0; r < LINII; r++)
        for (int c = 0; c < COLOANE; c++)
            grid[r][c] = 0;
}

void SpawnPiece()
{
    pieceType = rand() % 7;

    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            currentPiece[r][c] = pieces[pieceType][r][c];

    //coord de spawn
    blockX = COLOANE / 2 - 2;
    blockY = 0;

    
    //inainte sa spawnam data viitoare verificam daca mai are loc piesa
    if (!CanMove(blockX, blockY)) {
        state = MENU;
    }
}

//testam coliziunea
int CanMove(int newX, int newY)
{
    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 4; c++)
        {
            if (!currentPiece[r][c]) continue;

            int col = newX + c;
            int row = newY + r;

            if (col < 0 || col >= COLOANE) return 0;
            
            //nu se mai misca daca e pe podea
            if (row >= LINII-2) return 0;

            if (row < 0) continue; 

            //nu se mai misca daca sub el e alta piesa
            if (grid[row][col]) return 0;
        }
    }
    return 1;
}

void RotatePiece()
{
    int temp[4][4] = {0};

    //rotim matricea la 90 de grade
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            temp[c][3 - r] = currentPiece[r][c];
        }
    }

    int backup[4][4];
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            backup[r][c] = currentPiece[r][c];
            currentPiece[r][c] = temp[r][c];
        }
    }

    // Dacă rotația nu e posibila, revenim la starea de "backup"
    if (!CanMove(blockX, blockY)) {
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                currentPiece[r][c] = backup[r][c];
            }
        }
    }
}

void LockPiece()
{
    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 4; c++)
        {
            if (!currentPiece[r][c]) continue;

            int col = blockX + c;
            int row = blockY + r;

            if (row >= 0 && row < LINII && col >= 0 && col < COLOANE) {
                grid[row][col] = 1;
            }
        }
    }
}

void CheckLines()
{
    for (int r = LINII - 1; r >= 0; r--)
    {
        int lineFull = 1;
        for (int c = 0; c < COLOANE; c++) {
            if (grid[r][c] == 0) {
                lineFull = 0;
                break;
            }
        }

        if (lineFull) {
            for (int r2 = r; r2 > 0; r2--) {
                for (int c = 0; c < COLOANE; c++) {
                    grid[r2][c] = grid[r2 - 1][c];
                }
            }
            for (int c = 0; c < COLOANE; c++) {
                grid[0][c] = 0;
            }
            r++; 
        }
    }
}

void ScreenUpdate()
{
    Vector2 mouse = GetMousePosition();

    if (state == MENU)
    {
        if (CheckCollisionPointRec(mouse, startButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            state = GAME;
            for (int r = 0; r < LINII; r++)
                for (int c = 0; c < COLOANE; c++)
                    grid[r][c] = 0;
            SpawnPiece();
        }
        return;
    }

    UpdateInput(&input);

    if (input.left && CanMove(blockX - 1, blockY))   
        blockX -= 1;
    if (input.right && CanMove(blockX + 1, blockY))  
        blockX += 1;
    if (input.down && CanMove(blockX, blockY + 1))   
        blockY += 1;
    if (input.rotate)                                
        RotatePiece();

    fallTimer += GetFrameTime();

    if (fallTimer >= fallSpeed)
    {
        if (CanMove(blockX, blockY + 1))
        {
            blockY += 1;
        }
        else
        {
            LockPiece();
            CheckLines();
            SpawnPiece();
        }
        fallTimer = 0;
    }
}

void ScreenDraw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (state == MENU)
    {
        DrawText("TETRIS C", 360, 150, 40, BLACK);
        DrawRectangleRec(startButton, DARKGRAY);
        DrawText("START GAME", 385, 268, 20, WHITE);
        EndDrawing();
        return;
    }

    DrawRectangle(PLAY_X, PLAY_Y, PLAY_WIDTH, PLAY_HEIGHT, BLACK);
    
    for (int r = 0; r < LINII; r++)
    {
        for (int c = 0; c < COLOANE; c++)
        {
            if (grid[r][c])
            {
                DrawRectangle(PLAY_X + c * CELL_SIZE + 1, PLAY_Y + r * CELL_SIZE + 1, CELL_SIZE - 2, CELL_SIZE - 2, YELLOW);
            }
            else
            {
                DrawRectangleLines(PLAY_X + c * CELL_SIZE, PLAY_Y + r * CELL_SIZE, CELL_SIZE, CELL_SIZE, DARKGRAY);
            }
        }
    }

    //desenam piesa curenta 
    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 4; c++)
        {
            if (currentPiece[r][c])
            {
                int drawX = PLAY_X + (blockX + c) * CELL_SIZE;
                int drawY = PLAY_Y + (blockY + r) * CELL_SIZE;

               
                DrawRectangle(drawX + 1, drawY + 1, CELL_SIZE - 2, CELL_SIZE - 2, PINK);
                // grid interior pt claritate
                DrawRectangleLines(drawX, drawY, CELL_SIZE, CELL_SIZE, BLACK);
            }
        }
    }

    EndDrawing();
}