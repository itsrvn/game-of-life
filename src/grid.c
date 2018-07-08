#include "grid.h"

Grid *grid_new(int rows, int cols) {
    Grid *newGrid = malloc(sizeof(Grid));
    if (!newGrid) return NULL;

    newGrid->rows = rows;
    newGrid->cols = cols;

    newGrid->cells = malloc(rows * cols * sizeof(Cell));
    if (!newGrid->cells) return NULL;

    int i, j, cellCount = 0;

    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            Cell cell = {0, i, j};
            newGrid->cells[j + i * cols] = cell;
            cellCount++;
        }
    }

    newGrid->cellCount = cellCount;
    return newGrid;
}

int grid_get_alive_neighbors(Grid *srcGrid, int x, int y) {
    int rows = srcGrid->rows, cols = srcGrid->cols;

    int alive = 0;
    int pivot = y + x * cols;

    int i, j;
    for (i = -1; i <= 1; ++i) {
        for (j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            if (x >= 0 && x < rows && y >= 0 && y < cols) {
                if (srcGrid->cells[pivot + (i * cols) + j].state == 1) alive++;
            }
        }
    }

    return alive;
}

int grid_update(Grid *srcGrid) {
    int rows = srcGrid->rows, cols = srcGrid->cols;

    Cell *newCells = malloc(rows * cols * sizeof(Cell));
    if (!newCells) return EXIT_ERROR;

    int i, j;
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            Cell cell = srcGrid->cells[j + i * cols];
            int alive = grid_get_alive_neighbors(srcGrid, cell.x, cell.y);

            // check rules
            if (cell.state == 1) {
                if (alive < 2)
                    cell.state = 0;
                else if (alive == 2 || alive == 3)
                    cell.state = 1;
                else if (alive > 3)
                    cell.state = 0;
            } else if (alive == 3)
                cell.state = 1;

            // set new cell
            newCells[j + i * cols] = cell;
        }
    }

    // set current cells to new ones
    free(srcGrid->cells);
    srcGrid->cells = newCells;

    return OK;
}

void grid_update_pixels(Grid *srcGrid, unsigned char *pixels) {
    int i, cellCount = srcGrid->cellCount;
    for (i = 0; i < cellCount; ++i) {
        Cell cell = srcGrid->cells[i];
        const int offset = (srcGrid->rows * 4 * cell.y) + cell.x * 4;

        if (cell.state == 0) {
            pixels[offset + 0] = COLOR_DEAD_B;
            pixels[offset + 1] = COLOR_DEAD_G;
            pixels[offset + 2] = COLOR_DEAD_R;
        } else if (cell.state == 1) {
            pixels[offset + 0] = COLOR_ALIVE_B;
            pixels[offset + 1] = COLOR_ALIVE_G;
            pixels[offset + 2] = COLOR_ALIVE_R;
        }
        pixels[offset + 3] = 255;
    }
}

void grid_reset(Grid *srcGrid) {
    int i, cellCount = srcGrid->cellCount;
    for (i = 0; i < cellCount; ++i) {
        srcGrid->cells[i].state = 0;
    }
}

void grid_destroy(Grid *srcGrid) {
    free(srcGrid->cells);
    free(srcGrid);
}
