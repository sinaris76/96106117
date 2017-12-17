#include "physics.h"
#include "game.h"
#include "map.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define LOG(x) printf("%s = %d\n", #x, x)


Direction decideGhost(const Map* map, Ghost* ghost) {
    static Direction temp;
    int random = rand() % 4 + 1;
    if ((Direction) random == DIR_LEFT) {
        if ( ((int)ghost->x - 1) < 0) {
            if (map->cells[map->width - 1][(int) ghost->y] == CELL_BLOCK && temp == DIR_LEFT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)ghost->x][0] == CELL_BLOCK && temp == DIR_DOWN) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[0][(int)ghost->y] == CELL_BLOCK && temp == DIR_RIGHT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)ghost->x][map->height - 1] == CELL_BLOCK && temp == DIR_UP) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
        }
        if (map->cells[(int)ghost->x - 1][(int)ghost->y] == CELL_BLOCK && temp == DIR_LEFT) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)ghost->x][(int)ghost->y + 1] == CELL_BLOCK && temp == DIR_DOWN) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)ghost->x + 1][(int)ghost->y] == CELL_BLOCK && temp == DIR_RIGHT) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)ghost->x][(int)ghost->y - 1] == CELL_BLOCK && temp == DIR_UP) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if ( ((int)ghost->x - 1) < 0)
            if (map->cells[map->width - 1][(int)ghost->y] == CELL_BLOCK && temp != DIR_LEFT)
                return temp;
        if (map->cells[(int)ghost->x - 1][(int)ghost->y] == CELL_BLOCK && temp != DIR_LEFT)
            return temp;
        temp = DIR_LEFT;
        return DIR_LEFT;
    }

    if ((Direction) random == DIR_DOWN) {
        if ( ((int)ghost->y + 1) > map->height - 1) {
            if (map->cells[map->width - 1][(int) ghost->y] == CELL_BLOCK && temp == DIR_LEFT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)ghost->x][0] == CELL_BLOCK && temp == DIR_DOWN) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[0][(int)ghost->y] == CELL_BLOCK && temp == DIR_RIGHT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)ghost->x][map->height - 1] == CELL_BLOCK && temp == DIR_UP) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
        }
        if (map->cells[(int)ghost->x - 1][(int)ghost->y] == CELL_BLOCK && temp == DIR_LEFT) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)ghost->x][(int)ghost->y + 1] == CELL_BLOCK && temp == DIR_DOWN) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)ghost->x + 1][(int)ghost->y] == CELL_BLOCK && temp == DIR_RIGHT) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)ghost->x][(int)ghost->y - 1] == CELL_BLOCK && temp == DIR_UP) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if ( (int)ghost->y + 1 > map->height - 1)
            if (map->cells[(int)ghost->x][0] == CELL_BLOCK && temp != DIR_DOWN) {
                return temp;
            }
        if (map->cells[(int)ghost->x][(int)ghost->y + 1] == CELL_BLOCK && temp != DIR_DOWN) {
            return temp;
        }
        temp = DIR_DOWN;
        return DIR_DOWN;
    }

    if ((Direction) random == DIR_RIGHT) {
        if ( (int)ghost->x + 1 > map->width - 1) {
            if (map->cells[map->width - 1][(int) ghost->y] == CELL_BLOCK && temp == DIR_LEFT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)ghost->x][0] == CELL_BLOCK && temp == DIR_DOWN) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[0][(int)ghost->y] == CELL_BLOCK && temp == DIR_RIGHT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)ghost->x][map->height - 1] == CELL_BLOCK && temp == DIR_UP) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
        }
        if (map->cells[(int)ghost->x - 1][(int)ghost->y] == CELL_BLOCK && temp == DIR_LEFT) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)ghost->x][(int)ghost->y + 1] == CELL_BLOCK && temp == DIR_DOWN) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)ghost->x + 1][(int)ghost->y] == CELL_BLOCK && temp == DIR_RIGHT) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)ghost->x][(int)ghost->y - 1] == CELL_BLOCK && temp == DIR_UP) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if ( (int)ghost->x + 1 > map->width - 1)
            if (map->cells[0][(int)ghost->y] == CELL_BLOCK && temp != DIR_RIGHT)
                return temp;
        if (map->cells[(int)ghost->x + 1][(int)ghost->y] == CELL_BLOCK && temp != DIR_RIGHT)
            return temp;
        temp = DIR_RIGHT;
        return DIR_RIGHT;
    }

    if ((Direction) random == DIR_UP) {
        if ( (int)ghost->y - 1 < 0) {
            if (map->cells[map->width - 1][(int) ghost->y] == CELL_BLOCK && temp == DIR_LEFT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)ghost->x][0] == CELL_BLOCK && temp == DIR_DOWN) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[0][(int)ghost->y] == CELL_BLOCK && temp == DIR_RIGHT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)ghost->x][map->height - 1] == CELL_BLOCK && temp == DIR_UP) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
        }
        if (map->cells[(int)ghost->x - 1][(int)ghost->y] == CELL_BLOCK && temp == DIR_LEFT) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)ghost->x][(int)ghost->y + 1] == CELL_BLOCK && temp == DIR_DOWN) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)ghost->x + 1][(int)ghost->y] == CELL_BLOCK && temp == DIR_RIGHT) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)ghost->x][(int)ghost->y - 1] == CELL_BLOCK && temp == DIR_UP) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if ( (int)ghost->y - 1 < 0)
            if (map->cells[(int)ghost->x][map->height - 1] == CELL_BLOCK && temp != DIR_UP)
                return temp;
        if (map->cells[(int)ghost->x][(int)ghost->y - 1] == CELL_BLOCK && temp != DIR_UP)
            return temp;
        temp = DIR_UP;
        return DIR_UP;
    }
    return (Direction) random;

}

Direction decidePacman(const Map* map, Pacman* pacman, Action action) {
    //pacman->speed = (double) PACMAN_DEFAULT_SPEED;
    LOG(pacman->dir);
    static Direction temp;

    if (action == ACTION_LEFT) {
        if ( ((int)pacman->x - 1) < 0) {
            if (map->cells[map->width - 1][(int) pacman->y] == CELL_BLOCK && temp == DIR_LEFT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)pacman->x][0] == CELL_BLOCK && temp == DIR_DOWN) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[0][(int)pacman->y] == CELL_BLOCK && temp == DIR_RIGHT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)pacman->x][map->height - 1] == CELL_BLOCK && temp == DIR_UP) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
        }
        if (map->cells[(int)pacman->x - 1][(int)pacman->y] == CELL_BLOCK && temp == DIR_LEFT) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)pacman->x][(int)pacman->y + 1] == CELL_BLOCK && temp == DIR_DOWN) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)pacman->x + 1][(int)pacman->y] == CELL_BLOCK && temp == DIR_RIGHT) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)pacman->x][(int)pacman->y - 1] == CELL_BLOCK && temp == DIR_UP) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if ( ((int)pacman->x - 1) < 0)
            if (map->cells[map->width - 1][(int)pacman->y] == CELL_BLOCK && temp != DIR_LEFT)
                return temp;
        if (map->cells[(int)pacman->x - 1][(int)pacman->y] == CELL_BLOCK && temp != DIR_LEFT)
            return temp;
        temp = DIR_LEFT;
        return DIR_LEFT;
    }

    else if (action == ACTION_DOWN) {
        if ( ((int)pacman->y + 1) > map->height - 1) {
            if (map->cells[map->width - 1][(int) pacman->y] == CELL_BLOCK && temp == DIR_LEFT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)pacman->x][0] == CELL_BLOCK && temp == DIR_DOWN) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[0][(int)pacman->y] == CELL_BLOCK && temp == DIR_RIGHT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)pacman->x][map->height - 1] == CELL_BLOCK && temp == DIR_UP) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
        }
        if (map->cells[(int)pacman->x - 1][(int)pacman->y] == CELL_BLOCK && temp == DIR_LEFT) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)pacman->x][(int)pacman->y + 1] == CELL_BLOCK && temp == DIR_DOWN) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)pacman->x + 1][(int)pacman->y] == CELL_BLOCK && temp == DIR_RIGHT) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)pacman->x][(int)pacman->y - 1] == CELL_BLOCK && temp == DIR_UP) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if ( (int)pacman->y + 1 > map->height - 1)
            if (map->cells[(int)pacman->x][0] == CELL_BLOCK && temp != DIR_DOWN) {
                return temp;
            }
        if (map->cells[(int)pacman->x][(int)pacman->y + 1] == CELL_BLOCK && temp != DIR_DOWN) {
            return temp;
        }
        temp = DIR_DOWN;
        return DIR_DOWN;
    }

    else if (action == ACTION_RIGHT) {
        if ( (int)pacman->x + 1 > map->width - 1) {
            if (map->cells[map->width - 1][(int) pacman->y] == CELL_BLOCK && temp == DIR_LEFT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)pacman->x][0] == CELL_BLOCK && temp == DIR_DOWN) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[0][(int)pacman->y] == CELL_BLOCK && temp == DIR_RIGHT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)pacman->x][map->height - 1] == CELL_BLOCK && temp == DIR_UP) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
        }
        if (map->cells[(int)pacman->x - 1][(int)pacman->y] == CELL_BLOCK && temp == DIR_LEFT) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)pacman->x][(int)pacman->y + 1] == CELL_BLOCK && temp == DIR_DOWN) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)pacman->x + 1][(int)pacman->y] == CELL_BLOCK && temp == DIR_RIGHT) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)pacman->x][(int)pacman->y - 1] == CELL_BLOCK && temp == DIR_UP) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if ( (int)pacman->x + 1 > map->width - 1)
            if (map->cells[0][(int)pacman->y] == CELL_BLOCK && temp != DIR_RIGHT)
                return temp;
        if (map->cells[(int)pacman->x + 1][(int)pacman->y] == CELL_BLOCK && temp != DIR_RIGHT)
            return temp;
        temp = DIR_RIGHT;
        return DIR_RIGHT;
    }

    else if (action == ACTION_UP) {
        if ( (int)pacman->y - 1 < 0) {
            if (map->cells[map->width - 1][(int) pacman->y] == CELL_BLOCK && temp == DIR_LEFT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)pacman->x][0] == CELL_BLOCK && temp == DIR_DOWN) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[0][(int)pacman->y] == CELL_BLOCK && temp == DIR_RIGHT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)pacman->x][map->height - 1] == CELL_BLOCK && temp == DIR_UP) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
        }
        if (map->cells[(int)pacman->x - 1][(int)pacman->y] == CELL_BLOCK && temp == DIR_LEFT) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)pacman->x][(int)pacman->y + 1] == CELL_BLOCK && temp == DIR_DOWN) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)pacman->x + 1][(int)pacman->y] == CELL_BLOCK && temp == DIR_RIGHT) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if (map->cells[(int)pacman->x][(int)pacman->y - 1] == CELL_BLOCK && temp == DIR_UP) {
            temp = DIR_NONE;
            return DIR_NONE;
        }
        if ( (int)pacman->y - 1 < 0)
            if (map->cells[(int)pacman->x][map->height - 1] == CELL_BLOCK && temp != DIR_UP)
                return temp;
        if (map->cells[(int)pacman->x][(int)pacman->y - 1] == CELL_BLOCK && temp != DIR_UP)
            return temp;
        temp = DIR_UP;
        return DIR_UP;
    }
    else {
        if (pacman->dir == DIR_LEFT) {
            if ( ((int)pacman->x - 1) < 0) {
                if (map->cells[map->width - 1][(int) pacman->y] == CELL_BLOCK && temp == DIR_LEFT) {
                    temp = DIR_NONE;
                    return DIR_NONE;
                }
                if (map->cells[(int)pacman->x][0] == CELL_BLOCK && temp == DIR_DOWN) {
                    temp = DIR_NONE;
                    return DIR_NONE;
                }
                if (map->cells[0][(int)pacman->y] == CELL_BLOCK && temp == DIR_RIGHT) {
                    temp = DIR_NONE;
                    return DIR_NONE;
                }
                if (map->cells[(int)pacman->x][map->height - 1] == CELL_BLOCK && temp == DIR_UP) {
                    temp = DIR_NONE;
                    return DIR_NONE;
                }
            }
            if (map->cells[(int)pacman->x - 1][(int)pacman->y] == CELL_BLOCK && temp == DIR_LEFT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)pacman->x][(int)pacman->y + 1] == CELL_BLOCK && temp == DIR_DOWN) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)pacman->x + 1][(int)pacman->y] == CELL_BLOCK && temp == DIR_RIGHT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)pacman->x][(int)pacman->y - 1] == CELL_BLOCK && temp == DIR_UP) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if ( ((int)pacman->x - 1) < 0)
                if (map->cells[map->width - 1][(int)pacman->y] == CELL_BLOCK && temp != DIR_LEFT)
                    return temp;
            if (map->cells[(int)pacman->x - 1][(int)pacman->y] == CELL_BLOCK && temp != DIR_LEFT)
                return temp;
            temp = DIR_LEFT;
            return DIR_LEFT;
        }

        if (pacman->dir == DIR_DOWN) {
            if ( ((int)pacman->y + 1) > map->height - 1) {
                if (map->cells[map->width - 1][(int) pacman->y] == CELL_BLOCK && temp == DIR_LEFT) {
                    temp = DIR_NONE;
                    return DIR_NONE;
                }
                if (map->cells[(int)pacman->x][0] == CELL_BLOCK && temp == DIR_DOWN) {
                    temp = DIR_NONE;
                    return DIR_NONE;
                }
                if (map->cells[0][(int)pacman->y] == CELL_BLOCK && temp == DIR_RIGHT) {
                    temp = DIR_NONE;
                    return DIR_NONE;
                }
                if (map->cells[(int)pacman->x][map->height - 1] == CELL_BLOCK && temp == DIR_UP) {
                    temp = DIR_NONE;
                    return DIR_NONE;
                }
            }
            if (map->cells[(int)pacman->x - 1][(int)pacman->y] == CELL_BLOCK && temp == DIR_LEFT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)pacman->x][(int)pacman->y + 1] == CELL_BLOCK && temp == DIR_DOWN) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)pacman->x + 1][(int)pacman->y] == CELL_BLOCK && temp == DIR_RIGHT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)pacman->x][(int)pacman->y - 1] == CELL_BLOCK && temp == DIR_UP) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if ( (int)pacman->y + 1 > map->height - 1)
                if (map->cells[(int)pacman->x][0] == CELL_BLOCK && temp != DIR_DOWN) {
                    return temp;
                }
            if (map->cells[(int)pacman->x][(int)pacman->y + 1] == CELL_BLOCK && temp != DIR_DOWN) {
                return temp;
            }
            temp = DIR_DOWN;
            return DIR_DOWN;
        }

        if (pacman->dir == DIR_RIGHT) {
            if ( (int)pacman->x + 1 > map->width - 1) {
                if (map->cells[map->width - 1][(int) pacman->y] == CELL_BLOCK && temp == DIR_LEFT) {
                    temp = DIR_NONE;
                    return DIR_NONE;
                }
                if (map->cells[(int)pacman->x][0] == CELL_BLOCK && temp == DIR_DOWN) {
                    temp = DIR_NONE;
                    return DIR_NONE;
                }
                if (map->cells[0][(int)pacman->y] == CELL_BLOCK && temp == DIR_RIGHT) {
                    temp = DIR_NONE;
                    return DIR_NONE;
                }
                if (map->cells[(int)pacman->x][map->height - 1] == CELL_BLOCK && temp == DIR_UP) {
                    temp = DIR_NONE;
                    return DIR_NONE;
                }
            }
            if (map->cells[(int)pacman->x - 1][(int)pacman->y] == CELL_BLOCK && temp == DIR_LEFT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)pacman->x][(int)pacman->y + 1] == CELL_BLOCK && temp == DIR_DOWN) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)pacman->x + 1][(int)pacman->y] == CELL_BLOCK && temp == DIR_RIGHT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)pacman->x][(int)pacman->y - 1] == CELL_BLOCK && temp == DIR_UP) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if ( (int)pacman->x + 1 > map->width - 1)
                if (map->cells[0][(int)pacman->y] == CELL_BLOCK && temp != DIR_RIGHT)
                    return temp;
            if (map->cells[(int)pacman->x + 1][(int)pacman->y] == CELL_BLOCK && temp != DIR_RIGHT)
                return temp;
            temp = DIR_RIGHT;
            return DIR_RIGHT;
        }

        if (pacman->dir == DIR_UP) {
            if ( (int)pacman->y - 1 < 0) {
                if (map->cells[map->width - 1][(int) pacman->y] == CELL_BLOCK && temp == DIR_LEFT) {
                    temp = DIR_NONE;
                    return DIR_NONE;
                }
                if (map->cells[(int)pacman->x][0] == CELL_BLOCK && temp == DIR_DOWN) {
                    temp = DIR_NONE;
                    return DIR_NONE;
                }
                if (map->cells[0][(int)pacman->y] == CELL_BLOCK && temp == DIR_RIGHT) {
                    temp = DIR_NONE;
                    return DIR_NONE;
                }
                if (map->cells[(int)pacman->x][map->height - 1] == CELL_BLOCK && temp == DIR_UP) {
                    temp = DIR_NONE;
                    return DIR_NONE;
                }
            }
            if (map->cells[(int)pacman->x - 1][(int)pacman->y] == CELL_BLOCK && temp == DIR_LEFT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)pacman->x][(int)pacman->y + 1] == CELL_BLOCK && temp == DIR_DOWN) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)pacman->x + 1][(int)pacman->y] == CELL_BLOCK && temp == DIR_RIGHT) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if (map->cells[(int)pacman->x][(int)pacman->y - 1] == CELL_BLOCK && temp == DIR_UP) {
                temp = DIR_NONE;
                return DIR_NONE;
            }
            if ( (int)pacman->y - 1 < 0)
                if (map->cells[(int)pacman->x][map->height - 1] == CELL_BLOCK && temp != DIR_UP)
                    return temp;
            if (map->cells[(int)pacman->x][(int)pacman->y - 1] == CELL_BLOCK && temp != DIR_UP)
                return temp;
            temp = DIR_UP;
            return DIR_UP;
        }
    }
}
