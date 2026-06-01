#ifndef CONFIG_H
#define CONFIG_H

#define COLOANE 10
#define LINII 20

#define CELL_SIZE 30

//marimea tablei
#define PLAY_WIDTH  (COLOANE * CELL_SIZE)
#define PLAY_HEIGHT (LINII * CELL_SIZE)

#define SCREEN_WIDTH  900
#define SCREEN_HEIGHT 600

// centrarea 
#define PLAY_X ((SCREEN_WIDTH - PLAY_WIDTH) / 2)
#define PLAY_Y 60

#endif