#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

// Struct pentru input-ul curent
typedef struct {
    bool left;
    bool right;
    bool down;
    bool rotate;
} Input;

// Funcție care actualizează input-ul la fiecare frame
void UpdateInput(Input* input);

#endif // INPUT_H