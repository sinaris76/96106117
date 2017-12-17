#ifndef __MAP_H
#define __MAP_H

typedef enum {
    CELL_EMPTY= '_',
    CELL_BLOCK= '#',
    CELL_CHEESE= '*',
    CELL_CHERRY= '^',
    CELL_PINEAPPLE= 'O'
} Cell;

#define MAP_MAX_SIZE 100

typedef struct {
    int width;
    int height;
    Cell cells[MAP_MAX_SIZE][MAP_MAX_SIZE];
} Map;

#endif
