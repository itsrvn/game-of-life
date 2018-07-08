#ifndef GAME_OF_LIFE_GRID_H
#define GAME_OF_LIFE_GRID_H

#include <malloc.h>
#include "constants.h"

typedef struct _cell {
    int state;
    int x, y;
} Cell;

typedef struct _grid {
    int rows, cols;
    int cellCount;
    Cell *cells;
} Grid;

Grid *grid_new(int rows, int cols);

int grid_get_alive_neighbors(Grid *srcGrid, int x, int y);

int grid_update(Grid *srcGrid);

void grid_update_pixels(Grid *srcGrid, unsigned char *pixels);

void grid_reset(Grid *srcGrid);

void grid_destroy(Grid *srcGrid);

#endif  // GAME_OF_LIFE_GRID_H