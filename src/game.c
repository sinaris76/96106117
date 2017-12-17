#include "game.h"
#include "physics.h"
#include "map.h"
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define LOG(x) printf("%s = %d\n", #x, x)

void initiateGame(char* filename, Map* outMap, Game* outGame, Pacman* outPacman, Ghost* outGhosts) {
    srand((unsigned int) time(NULL));
    int i, j;
    FILE *map;
    map = fopen(filename, "r");
    fscanf(map, "%d %d", &outMap->height, &outMap->width);
    char temp[outMap->width + 1];
    for (i = 0; i < outMap->height; i++) {
        fscanf(map, "%s", temp);
        temp [outMap->width + 1] = '\0';
        for (j = 0; j < outMap->width; j++) {
            outMap->cells[j][i] = (Cell) temp[j];
            if (outMap->cells[j][i] == CELL_PINEAPPLE)
                outGame->pineapples += 1;
            if (outMap->cells[j][i] == CELL_CHEESE)
                outGame->cheeses += 1;
            if (outMap->cells[j][i] == CELL_CHERRY)
                outGame->cherries += 1;
        }
    }
    outGame->ghosts = MAX_GHOST_COUNT;
    fscanf(map, "%d%*s %d %d (%d,%d) (%lf,%lf)", &outGame->score, &outPacman->dir, &outPacman->health, &outPacman->startX, &outPacman->startY, &outPacman->x, &outPacman->y);
    for (i = 0; i < MAX_GHOST_COUNT; i++) {
        switch (i)
        {
            case 0:
                outGhosts[i].type = BLINKY; break;
            case 1:
                outGhosts[i].type = PINKY; break;
            case 2:
                outGhosts[i].type = CLYDE; break;
            case 3:
                outGhosts[i].type = INKY; break;

        }
        fscanf(map, "%*s %d %d ", &outGhosts[i].dir, &outGhosts[i].blue);
        if (outGhosts[i].blue == 0) {
            fscanf(map, "%llu ", &outGhosts[i].blueCounterDown);
            outGhosts[i].blueCounterDown *= CYCLES_PER_SEC;
        }
        else
            outGhosts[i].blueCounterDown = 0;
        if (outGhosts[i].blue == 0)
            outGhosts[i].blue = true;
        else
            outGhosts[i].blue = false;
        fscanf(map, "(%d,%d) (%lf,%lf)", &outGhosts[i].startX, &outGhosts[i].startY, &outGhosts[i].x, &outGhosts[i].y);
        outGhosts[i].speed= (double) GHOST_DEFAULT_SPEED;
    }
    outPacman->speed = (double )PACMAN_DEFAULT_SPEED;

}

void checkEatables(Map* map, Game* outGame, Pacman* outPacman, Ghost* outGhosts) {
        if (map->cells[(int) outPacman->x][(int) outPacman->y] == CELL_CHERRY &&
            (fabs(outPacman->x - (double) ((int) outPacman->x)) < 0.5) &&
            (fabs(outPacman->y - (double) ((int) outPacman->y)) < 0.5)) {
            outGame->score += CHERRY_SCORE;
            outGame->cherries -= 1;
            map->cells[(int) outPacman->x][(int) outPacman->y] = CELL_EMPTY;
        }
        if (map->cells[(int) outPacman->x][(int) outPacman->y] == CELL_PINEAPPLE &&
            (fabs(outPacman->x - (double) ((int) outPacman->x)) < 0.5) &&
            (fabs(outPacman->y - (double) ((int) outPacman->y)) < 0.5)) {
            outGame->score += PINEAPPLE_SCORE;
            outGame->pineapples -= 1;
            map->cells[(int) outPacman->x][(int) outPacman->y] = CELL_EMPTY;
            int i;
            for (i = 0; i < MAX_GHOST_COUNT; i++) {
                outGhosts[i].blue = true;
                outGhosts[i].blueCounterDown = BLUE_DURATION;
            }
        }
        if (map->cells[(int) outPacman->x][(int) outPacman->y] == CELL_CHEESE &&
            ((fabs(outPacman->x - (double) ((int) outPacman->x)) < 0.5)) &&
            (fabs(outPacman->y - (double) ((int) outPacman->y)) < 0.5)) {
            outGame->score += CHEESE_SCORE;
            outGame->cheeses -= 1;
            map->cells[(int) outPacman->x][(int) outPacman->y] = CELL_EMPTY;

        }
}

void checkGhostCollision(Pacman* outPacman, Ghost* outGhost) {
    if (fabs((outPacman->x - outGhost->x)) < 0.5 && fabs(outPacman->y - outGhost->y) < 0.5) {
        if (outGhost->blue == true) {
            outGhost->x = (float) outGhost->startX;
            outGhost->y = (float) outGhost->startY;
            outGhost->blue = false;
        }
        else {
            outPacman->x = (float) outPacman->startX;
            outPacman->y = (float) outPacman->startY;
            outPacman->health -= 1;
        }

    }
}

bool isGameFinished(Game* game, Pacman* pacman) {
    if (game->cheeses == 0 && game->pineapples == 0)
        return true;
    if (pacman->health == 0)
        return true;
    return false;
}

void checkGhostState(Ghost* ghost) {
    if (ghost->blue == true) {
        ghost->blueCounterDown -=1;
        if (ghost->blueCounterDown <= 0)
            ghost->blue = false;
    }
}
