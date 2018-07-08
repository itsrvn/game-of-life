#ifndef GAME_OF_LIFE_UTILS_H
#define GAME_OF_LIFE_UTILS_H

#include <stdlib.h>
#include <time.h>
#include "grid.h"

int random(int min, int max) {
    static int init = 0;
    if (!init) {
        srand((unsigned int)time(NULL));
        init = 1;
    }
    return rand() % max + min;
}

void grid_randomize(Grid *srcGrid, int state, int count) {
    int flattenState = state < 1 ? 0 : 1;
    int i, cellCount = srcGrid->cellCount;

    for (i = 0; i < count; ++i) {
        int randIndex = random(0, cellCount);
        srcGrid->cells[randIndex].state = flattenState;
    }
}

#endif  // GAME_OF_LIFE_UTILS_H