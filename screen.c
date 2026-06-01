#include "screen.h"
#include "measure.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

static GameState state;
static Rectangle startButton;
static Rectangle restartButton;
static Input input;

static int grid[LINII][COLOANE];
static int gridColors[LINII][COLOANE]; 

// sistemul de animatie pentru stergerea liniilor
static int isLineClearing[LINII]; //retine linia stearsa ca sa o coloreze diferit     
static float clearEffectTimer = 0.0f; //cronometrul tine animatia activa 0.3 sec 
static bool isAnimatingClear = false;  

//coordonatele piesei
static int blockX;
static int blockY;

static float fallTimer = 0;
static float fallSpeed = 0.5f; 

static int score = 0;
static float gameTime = 0.0f;

// Fontul elegant de tipar
static Font bookFont;
static int pieceType;
static int currentPiece[4][4];

static int pieces[7][4][4] = {
    
    // O
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    // I
    {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    // T
    {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    // L
    {
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    // J
    {
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    //S
    {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    //Z
    {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }
};


static Color pieceColors[8] = {
    BLACK,
    (Color){ 128, 40, 40, 255 },    // 1 - visiniu
    (Color){ 34, 76, 56, 255 },     // 2 - verde
    (Color){ 43, 58, 85, 255 },     // 3 - albastru
    (Color){ 197, 137, 64, 255 },   // 4 - galben
    (Color){ 92, 64, 109, 255 },    // 5 - mov
    (Color){ 141, 110, 99, 255 },   // 6 - maro
    (Color){ 210, 105, 30, 255 }    // 7 - maro deschis
};

void ScreenInit()
{
    state = MENU;
    startButton = (Rectangle){ (SCREEN_WIDTH - 220) / 2, 340, 220, 55 };
    restartButton = (Rectangle){ (SCREEN_WIDTH - 220) / 2, 420, 220, 55 };
    srand(time(NULL));

    bookFont = LoadFontEx("C:\\Windows\\Fonts\\georgia.ttf", 48, NULL, 0);
}

void ResetGame()
{
    score = 0;
    gameTime = 0.0f;
    fallSpeed = 0.5f;
    isAnimatingClear = false;
    clearEffectTimer = 0.0f;
    for (int r = 0; r < LINII; r++) {
        isLineClearing[r] = 0;
        for (int c = 0; c < COLOANE; c++) {
            grid[r][c] = 0;
            gridColors[r][c] = 0;
        }
    }
    SpawnPiece();
}

void SpawnPiece()
{
    pieceType = rand() % 7;
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            currentPiece[r][c] = pieces[pieceType][r][c];

    blockX = COLOANE / 2 - 2;
    blockY = -1; 

    if (!CanMove(blockX, blockY)) {
        state = GAME_OVER;
    }
}

int CanMove(int newX, int newY)
{
    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 4; c++)
        {
            //daca patratelul scanat e gol, nu ne intereseaza
            if (!currentPiece[r][c]) continue;

            int col = newX + c;
            int row = newY + r;

            if (col < 0 || col >= COLOANE || row >= LINII) return 0;
            if (row < 0) continue; 

            if (grid[row][col]) return 0;
        }
    }
    return 1;
}

void RotatePiece()
{
    int temp[4][4] = {0};
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

    if (!CanMove(blockX, blockY)) {
        if (CanMove(blockX + 1, blockY)) blockX += 1;
        else if (CanMove(blockX - 1, blockY)) blockX -= 1;
        else {
            for (int r = 0; r < 4; r++)
                for (int c = 0; c < 4; c++)
                    currentPiece[r][c] = backup[r][c];
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
                gridColors[row][col] = pieceType + 1;
            }
        }
    }
}

void CheckLines()
{
    int linesFound = 0;
    for (int r = 0; r < LINII; r++)
    {
        int lineFull = 1;
        for (int c = 0; c < COLOANE; c++) {
            if (grid[r][c] == 0) {
                lineFull = 0;
                break;
            }
        }
        if (lineFull) {
            isLineClearing[r] = 1; 
            linesFound++;
        }
    }

    if (linesFound > 0) {
        isAnimatingClear = true;
        clearEffectTimer = 0.3f; 

        if (linesFound == 1) score += 10;   
        else if (linesFound == 2) score += 30;
        else if (linesFound == 3) score += 55;
        else if (linesFound == 4) score += 90; 

        fallSpeed = 0.5f - (score / 5000.0f);
        if (fallSpeed < 0.15f) fallSpeed = 0.15f;
    }
}

void ExecuteLineDeletion()
{
    for (int r = LINII - 1; r >= 0; r--)
    {
        if (isLineClearing[r]) {
            isLineClearing[r] = 0; 
            for (int r2 = r; r2 > 0; r2--) {
                for (int c = 0; c < COLOANE; c++) {
                    grid[r2][c] = grid[r2 - 1][c];
                    gridColors[r2][c] = gridColors[r2 - 1][c];
                    isLineClearing[r2] = isLineClearing[r2 - 1];
                }
            }
            for (int c = 0; c < COLOANE; c++) {
                grid[0][c] = 0;
                gridColors[0][c] = 0;
            }
            isLineClearing[0] = 0;
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
            ResetGame();
        }
        return;
    }

    if (state == GAME_OVER)
    {
        if (CheckCollisionPointRec(mouse, restartButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            state = GAME;
            ResetGame();
        }
        return;
    }

    float dt = GetFrameTime();
    gameTime += dt; 

    if (isAnimatingClear) {
        clearEffectTimer -= dt;
        if (clearEffectTimer <= 0.0f) {
            isAnimatingClear = false;
            ExecuteLineDeletion(); 
            SpawnPiece(); 
        }
        return; 
    }

    UpdateInput(&input);

    if (input.left && CanMove(blockX - 1, blockY))   blockX -= 1;
    if (input.right && CanMove(blockX + 1, blockY))  blockX += 1;
    if (input.rotate)                                RotatePiece();

    fallTimer += dt;
    float currentFallSpeed = input.down ? 0.04f : fallSpeed;

    if (fallTimer >= currentFallSpeed)
    {
        if (CanMove(blockX, blockY + 1))
        {
            blockY += 1;
        }
        else
        {
            LockPiece();
            CheckLines();
            if (!isAnimatingClear) { 
                SpawnPiece(); 
            }
        }
        fallTimer = 0;
    }
}

void DrawTextCentered(const char* text, int posY, int fontSize, Color color)
{
    Vector2 textSize = MeasureTextEx(bookFont, text, (float)fontSize, 1.0f);
    Vector2 position = { (float)SCREEN_WIDTH / 2 - textSize.x / 2, (float)posY };
    DrawTextEx(bookFont, text, position, (float)fontSize, 1.0f, color);
}

void DrawBookStack(int x, int y)
{
    
    DrawRectangle(x, y, 160, 24, (Color){ 128, 40, 40, 255 });
    DrawRectangle(x + 154, y + 4, 6, 16, WHITE); // Pagini tăiate
    
    DrawRectangle(x + 10, y - 20, 145, 20, (Color){ 34, 76, 56, 255 });
    DrawRectangle(x + 148, y - 16, 7, 12, WHITE);
    
    DrawRectangle(x + 5, y - 36, 150, 16, (Color){ 197, 137, 64, 255 });
    DrawRectangle(x + 148, y - 32, 7, 8, WHITE);

    DrawRectangle(x + 25, y - 51, 115, 15, (Color){ 43, 58, 85, 255 });
    DrawRectangle(x + 133, y - 48, 7, 9, WHITE);
}


void ScreenDraw()
{
    BeginDrawing();
    ClearBackground((Color){ 250, 223, 204, 255 }); 

    char pagesStr[30];
    char timeStr[30];
    sprintf(pagesStr, "%d pag.", score);
    sprintf(timeStr, "%d sec", (int)gameTime);

    Color textDark = (Color){ 62, 46, 36, 255 }; 

    if (state == MENU)
    {
        DrawTextCentered("Cozy Bookish Tetris", 130, 46, textDark);
        DrawTextCentered("@lightwood.book, clear your mind", 195, 18, (Color){ 110, 85, 72, 255 });
        
        bool hover = CheckCollisionPointRec(GetMousePosition(), startButton);
        DrawRectangleRounded(startButton, 0.2f, 4, hover ? (Color){ 219, 172, 141, 255 } : (Color){ 237, 201, 175, 255 });
        DrawRectangleRoundedLinesEx(startButton, 0.2f, 4, 2, textDark);
        
        Vector2 bSize = MeasureTextEx(bookFont, "OPEN BOOK 📖", 19, 1.0f);
        DrawTextEx(bookFont, "OPEN BOOK 📖", (Vector2){ startButton.x + startButton.width/2 - bSize.x/2, startButton.y + 17 }, 19, 1.0f, textDark);
        
        DrawBookStack(SCREEN_WIDTH / 2 - 80, 520);

        EndDrawing();
        return;
    }

    if (state == GAME_OVER)
    {
        DrawTextCentered("Reading Session Ended ☕", 120, 38, textDark);
        
        DrawRectangleRounded((Rectangle){ SCREEN_WIDTH / 2 - 150, 200, 300, 140 }, 0.15f, 4, (Color){ 255, 243, 235, 255 });
        DrawRectangleRoundedLinesEx((Rectangle){ SCREEN_WIDTH / 2 - 150, 200, 300, 140 }, 0.15f, 4, 2, textDark);
        
        char finalPages[50];
        char finalTime[50];
        sprintf(finalPages, "Total Progress: %d pages", score);
        sprintf(finalTime, "Reading Time: %.1fs", gameTime);
        
        DrawTextCentered(finalPages, 230, 18, textDark);
        DrawTextCentered(finalTime, 280, 18, (Color){ 110, 85, 72, 255 });

        bool hover = CheckCollisionPointRec(GetMousePosition(), restartButton);
        DrawRectangleRounded(restartButton, 0.2f, 4, hover ? (Color){ 219, 172, 141, 255 } : (Color){ 237, 201, 175, 255 });
        DrawRectangleRoundedLinesEx(restartButton, 0.2f, 4, 2, textDark);
        
        Vector2 rSize = MeasureTextEx(bookFont, "READ AGAIN 📑", 19, 1.0f);
        DrawTextEx(bookFont, "READ AGAIN 📑", (Vector2){ restartButton.x + restartButton.width/2 - rSize.x/2, restartButton.y + 17 }, 19, 1.0f, textDark);
        
        EndDrawing();
        return;
    }

    
    DrawRectangle(PLAY_X, PLAY_Y, PLAY_WIDTH, PLAY_HEIGHT + 4, (Color){ 253, 251, 247, 255 });
    DrawRectangleLinesEx((Rectangle){ PLAY_X - 3, PLAY_Y - 3, PLAY_WIDTH + 6, PLAY_HEIGHT + 7 }, 3, textDark);

    for (int r = 0; r < LINII; r++)
    {
        //animatie
        if (isLineClearing[r]) {
            DrawRectangle(PLAY_X, PLAY_Y + r * CELL_SIZE, PLAY_WIDTH, CELL_SIZE, (Color){ 255, 237, 133, 255 });
            continue;
        }

        for (int c = 0; c < COLOANE; c++)
        {
            int startCellX = PLAY_X + c * CELL_SIZE;
            int startCellY = PLAY_Y + r * CELL_SIZE;

            if (grid[r][c])
            {
                int colorIdx = gridColors[r][c];

               
                DrawRectangle(startCellX + 1, startCellY + 1, CELL_SIZE - 2, CELL_SIZE - 2, pieceColors[colorIdx]);
               
                DrawRectangle(startCellX + 3, startCellY + CELL_SIZE / 2 - 1, CELL_SIZE - 6, 2, (Color){ 255, 255, 255, 80 });
                DrawRectangleLines(startCellX, startCellY, CELL_SIZE, CELL_SIZE, (Color){ 62, 46, 36, 50 });
            }
            else
            {
                
                DrawRectangleLines(startCellX, startCellY, CELL_SIZE, CELL_SIZE, (Color){ 62, 46, 36, 12 });
            }
        }
    }

    if (!isAnimatingClear) {
        for (int r = 0; r < 4; r++)
        {
            for (int c = 0; c < 4; c++)
            {
                if (currentPiece[r][c])
                {
                    int drawX = PLAY_X + (blockX + c) * CELL_SIZE;
                    int drawY = PLAY_Y + (blockY + r) * CELL_SIZE;

                    if (drawY >= PLAY_Y && drawY < PLAY_Y + PLAY_HEIGHT) {
                        DrawRectangle(drawX + 1, drawY + 1, CELL_SIZE - 2, CELL_SIZE - 2, pieceColors[pieceType + 1]);
                        DrawRectangle(drawX + 3, drawY + CELL_SIZE / 2 - 1, CELL_SIZE - 6, 2, (Color){ 255, 255, 255, 90 });
                        DrawRectangleLines(drawX, drawY, CELL_SIZE, CELL_SIZE, textDark);
                    }
                }
            }
        }
    }

    //UI-ul din dreapta ecranului
    int panelX = PLAY_X + PLAY_WIDTH + 50;
    
    // widget 1 : pagini citite
    DrawRectangleRounded((Rectangle){ panelX, PLAY_Y, 280, 85 }, 0.15f, 4, (Color){ 253, 251, 247, 255 });
    DrawRectangleRoundedLinesEx((Rectangle){ panelX, PLAY_Y, 280, 85 }, 0.15f, 4, 1, textDark);
    DrawTextEx(bookFont, "📖 PAGES READ", (Vector2){ panelX + 20, PLAY_Y + 15 }, 14, 1.0f, (Color){ 120, 90, 75, 255 });
    DrawTextEx(bookFont, pagesStr, (Vector2){ panelX + 20, PLAY_Y + 36 }, 30, 1.0f, textDark);

    // widget 2: "reading session"
    DrawRectangleRounded((Rectangle){ panelX, PLAY_Y + 115, 280, 85 }, 0.15f, 4, (Color){ 253, 251, 247, 255 });
    DrawRectangleRoundedLinesEx((Rectangle){ panelX, PLAY_Y + 115, 280, 85 }, 0.15f, 4, 1, textDark);
    DrawTextEx(bookFont, "☕ READING SESSION", (Vector2){ panelX + 20, PLAY_Y + 130 }, 14, 1.0f, (Color){ 120, 90, 75, 255 });
    DrawTextEx(bookFont, timeStr, (Vector2){ panelX + 20, PLAY_Y + 153 }, 30, 1.0f, textDark);

    // Gcontroale
    DrawTextEx(bookFont, "BOOKMARK CONTROLS:", (Vector2){ panelX, PLAY_Y + 240 }, 15, 1.0f, textDark);
    DrawTextEx(bookFont, "📑 Left / Right : Flip layout", (Vector2){ panelX, PLAY_Y + 268 }, 14, 1.0f, (Color){ 90, 75, 65, 255 });
    DrawTextEx(bookFont, "📑 Up / Space   : Rotate binding", (Vector2){ panelX, PLAY_Y + 293 }, 14, 1.0f, (Color){ 90, 75, 65, 255 });
    DrawTextEx(bookFont, "📑 Down         : Fast scan page", (Vector2){ panelX, PLAY_Y + 318 }, 14, 1.0f, (Color){ 90, 75, 65, 255 });

    
    DrawBookStack(panelX + 40, PLAY_Y + 390);

    EndDrawing();
}