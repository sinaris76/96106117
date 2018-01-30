#ifndef __GAME_H
#define __GAME_H

#include <stdbool.h>
#include "map.h"

typedef enum { 
    DIR_UP = 1,
    DIR_RIGHT = 2,
    DIR_DOWN = 3,
    DIR_LEFT = 4,
    DIR_NONE = -1 } Direction;

typedef enum { BLINKY, PINKY, CLYDE, INKY } GhostType;

#define MAX_GHOST_COUNT 4
#define MINUMAL_DISTANCE 1
#define CHEESE_SCORE 10
#define CHERRY_SCORE 100
#define PINEAPPLE_SCORE 20

typedef struct {
    int score;
    int cheeses, cherries, pineapples;
    int ghosts;
} Game;

typedef struct {
    double x, y;
    int startX, startY;
    Direction dir;
    int health;
    double speed;
} Pacman;

#define CYCLES_PER_SEC 60
#define BLUE_DURATION 5*CYCLES_PER_SEC
typedef enum {
    CHASE = 1,
    SCATTER = 2 } GhostState;

typedef struct {
    double x, y;
    int startX, startY;
    Direction dir;
    GhostType type;
    bool blue;
    GhostState state;
    unsigned long long blueCounterDown;
    unsigned long long stateCounterDown;
    double speed;
} Ghost;

// TO WRITE
void initiateGame(char* filename, Map* outMap, Game* outGame, Pacman* outPacman, Ghost* outGhosts);

// TO WRITE
void checkEatables(Map* map, Game* outGame, Pacman* outPacman, Ghost* outGhosts);

// TO WRITE
void checkGhostCollision(Pacman* outPacman, Ghost* outGhost);

// TO WRITE
bool isGameFinished(Game* game, Pacman* pacman);

// TO WRITE
void checkGhostState(Ghost* ghost);
#endif