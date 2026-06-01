#ifndef SCREEN_H
#define SCREEN_H

#include "raylib.h"
#include "input.h"
#include "measure.h"

typedef enum {
    MENU,
    GAME,
    GAME_OVER
} GameState;

void ScreenInit();
void ScreenUpdate();
void ScreenDraw();

void LockPiece();
void SpawnPiece();
int CanMove(int newX, int newY);
void RotatePiece();
void CheckLines();

#endif