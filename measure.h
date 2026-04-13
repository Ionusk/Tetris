#ifndef CONFIG_H
#define CONFIG_H

#define COLOANE 10
#define LINII 20
#define CELL_SIZE 30

#define PLAY_WIDTH (COLOANE * CELL_SIZE)
#define PLAY_HEIGHT (LINII * CELL_SIZE)

#define PLAY_X ((800 - PLAY_WIDTH) / 2)
#define PLAY_Y ((600 - PLAY_HEIGHT) / 2)

#endif