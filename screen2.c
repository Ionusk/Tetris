/*
#include "screen.h"

//ecranul de start
void ScreenInit()
{
    state = MENU;
    startButton = (Rectangle){300, 200, 200, 60};
}

//se executa la fiecare frame
void ScreenUpdate()
{
    Vector2 mouse = GetMousePosition();

    if (state == MENU)
    {
        if (CheckCollisionPointRec(mouse, startButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            //daca suntem in meniu si utilizatorul apasa "click stanga" pe butonul de start, vom incepe jocul cu spawnare de piese
            state = GAME;
            SpawnPiece();
        }
        return;
    }

    //citim input de la tastatura
    UpdateInput(&input);

    if (input.left && CanMove(blockX - CELL_SIZE, blockY))
        blockX -= CELL_SIZE;

    if (input.right && CanMove(blockX + CELL_SIZE, blockY))
        blockX += CELL_SIZE;

    if (input.down && CanMove(blockX, blockY + CELL_SIZE))
        blockY += CELL_SIZE;


    //adunam timpul de la ultimul frame
    fallTimer += GetFrameTime();

    if (fallTimer >= fallSpeed)
    {
        //daca au trecut 0.4 secunde si poate cobori in jos, coboara
        if (CanMove(blockX, blockY + CELL_SIZE))
        {
            blockY += CELL_SIZE;
        }
        else
        //daca nu mai e loc, plasam piesa jos de tot si spawnam alta
        {
            LockPiece();
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
        DrawText("TETRIS", 320, 100, 40, BLACK);
        DrawRectangleRec(startButton, GRAY);
        DrawText("START GAME", 330, 220, 20, BLACK);
        DrawText("PRESS Q TO EXIT", 330, 400, 40, BLACK);
    }
    else
    {
        DrawRectangle(PLAY_X, PLAY_Y, PLAY_WIDTH, PLAY_HEIGHT, PURPLE);

        for (int l = 0; l < LINII; l++)
        {
            for (int c = 0; c < COLOANE; c++)
            {
                if (grid[l][c])
                {
                    DrawRectangle(
                        PLAY_X + c * CELL_SIZE, //pozitie pe orizontala
                        PLAY_Y + l * CELL_SIZE, //pozitie pe verticala
                        CELL_SIZE, //latime
                        CELL_SIZE, //inaltime
                        YELLOW
                    );
                }
            }
        }

        DrawRectangle(blockX, blockY, CELL_SIZE, CELL_SIZE, PINK);
        DrawRectangle(blockX + CELL_SIZE, blockY, CELL_SIZE, CELL_SIZE, PINK);
        DrawRectangle(blockX, blockY + CELL_SIZE, CELL_SIZE, CELL_SIZE, PINK);
        DrawRectangle(blockX + CELL_SIZE, blockY + CELL_SIZE, CELL_SIZE, CELL_SIZE, PINK);
    }

    EndDrawing();
}


void LockPiece()
{
    int col = (blockX - PLAY_X) / CELL_SIZE;
    int row = (blockY - PLAY_Y) / CELL_SIZE;

    grid[row][col] = 1;
    grid[row][col + 1] = 1;
    grid[row + 1][col] = 1;
    grid[row + 1][col + 1] = 1;
}

void SpawnPiece()
{
    blockX = PLAY_X + (COLOANE / 2) * CELL_SIZE;
    blockY = PLAY_Y;
}


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

        if (c < 0 || c >= COLOANE || r < 0 || r >= LINII)
            return 0;

        if (grid[r][c])
            return 0;
    }

    return 1;
}
*/