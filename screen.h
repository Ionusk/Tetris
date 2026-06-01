#ifndef SCREEN_H
#define SCREEN_H

#include "raylib.h"
#include "input.h"
#include "measure.h"

typedef enum {
    MENU,
    GAME
} GameState;


static GameState state;
static Rectangle startButton;
static Input input;

static int grid[LINII][COLOANE];

static int blockX;
static int blockY;

static float fallTimer = 0;
static float fallSpeed = 0.6f;

static int pieces[7][4][4] = {
    { {1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0} }, // O
    { {0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0} }, // I
    { {0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0} }, // T
    { {0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0} }, // L
    { {1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0} }, // J
    { {0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0} }, // S
    { {1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0} }  // Z
};

static int currentPiece[4][4];
static int pieceType;

void ScreenInit();
void ScreenUpdate();
void ScreenDraw();

void LockPiece();
void SpawnPiece();
int CanMove(int newX, int newY);
void RotatePiece();
void CheckLines();

#endif