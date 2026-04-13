#ifndef INPUT_H
#define INPUT_H
#include <stdbool.h>

typedef struct {
    bool left;
    bool right;
    bool down;
    bool rotate;
} Input;

void UpdateInput(Input* input);

#endif 