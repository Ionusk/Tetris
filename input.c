#include "input.h"
#include "raylib.h"


void UpdateInput(Input* input)
{
    if (!input) return;

    float dt = GetFrameTime(); //delta time masoare cat timp a trecut intre cadrul precedent si cel actual

    //resetam miscarile
    input->left  = false;
    input->right = false;

    //daca sageata stanga e doar apasata
    if (IsKeyPressed(KEY_LEFT)) {
        input->left = true; 
        input->leftHold = 0; //setam holdul la 0, ca nu e tinut apasat
    }

    //daca e tinut apasat:
    else if (IsKeyDown(KEY_LEFT)) {
        //"cronometrul" lefthold adauga timp (delta time)
        input->leftHold += dt;

        if (input->leftHold >= 0.18f) { //dupa 0.18 secunde de tinut apasata tasta, piesa se misca mai repede
            input->left = true;
            input->leftHold -= 0.05f; //daca dupa 0.05 secunde e tot apasata, o sa coboare din nou
        }
    }
    //daca iei degetul de pe tasta, cronometrul se reseteaza la 0
    else {
        input->leftHold = 0;
    }

    if (IsKeyPressed(KEY_RIGHT)) {
        input->right = true;
        input->rightHold = 0;
    }
    else if (IsKeyDown(KEY_RIGHT)) {
        input->rightHold += dt;
        if (input->rightHold >= 0.18f) {
            input->right = true;
            input->rightHold -= 0.05f;
        }
    }
    else {
        input->rightHold = 0;
    }

    input->down = IsKeyDown(KEY_DOWN);
    input->rotate = IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_SPACE);
}