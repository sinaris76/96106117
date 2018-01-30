#ifndef __PHYSICS_H
#define __PHYSICS_H

#include "game.h"
#include "input.h"

#define PACMAN_DEFAULT_SPEED 2.
#define GHOST_DEFAULT_SPEED 2.

// TO WRITE
Direction decidePacman(const Map* map, Pacman* pacman, Action action);

// TO WRITE
Direction BFS(const Map *map, int origin_x, int origin_y, int dest_x, int dest_y);

Direction decideGhost(const Map* map, Ghost* ghost, Pacman *pacman, Ghost *blinky);
#endif