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
static int grid[LINII][COLOANE] = {0};
static int blockX;
static int blockY;
static float fallTimer = 0;
static float fallSpeed = 0.4f;

void ScreenInit();
void ScreenUpdate();
void ScreenDraw();

void LockPiece();
void SpawnPiece();
int CanMove(int newX, int newY);

#endif