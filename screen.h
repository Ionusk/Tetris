#ifndef SCREEN_H
#define SCREEN_H

#include "raylib.h"
#include "input.h"

#define COLOANE 10
#define RANDURI 20
#define CELL_SIZE 30

#define PLAY_WIDTH (COLOANE * CELL_SIZE)
#define PLAY_HEIGHT (RANDURI * CELL_SIZE)

#define PLAY_X ((800 - PLAY_WIDTH) / 2)
#define PLAY_Y ((600 - PLAY_HEIGHT) / 2)


typedef enum {
    MENU,
    GAME
} GameState;

static GameState state;
static Rectangle startButton;
static Input input;
static int grid[RANDURI][COLOANE] = {0};
static int blockX;
static int blockY;
static float fallTimer = 0;
static float fallSpeed = 0.4f;


void ScreenInit();
void ScreenUpdate();
void ScreenDraw();

#endif