#include "physics.h"
#include "game.h"
#include "map.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include<math.h>

#define LOG(x) printf("%s = %d\n", #x, x)

Direction BFS(const Map *map, int origin_x, int origin_y, int dest_x, int dest_y) {
    srand(time(NULL));
    if (origin_x == dest_x && origin_y == (dest_y - 1 >= 0 ? dest_y - 1 : map->height - 1))
        return DIR_DOWN;
    if (origin_x == dest_x && origin_y == (dest_y + 1 <= map->height - 1 ? dest_y + 1 : 0))
        return DIR_UP;
    if (origin_y == dest_y && origin_x == (dest_x - 1 >= 0 ? dest_x - 1 : map->width - 1))
        return DIR_RIGHT;
    if (origin_y == dest_y && origin_x == (dest_x + 1 <= map->width - 1 ? dest_x + 1 : 0))
        return DIR_LEFT;
    if (origin_x == dest_x && origin_y == dest_y) {
        int random = rand() % 4 + 1;
        if (map->cells[(origin_x + 1 <= map->width - 1) ? origin_x + 1 : 0][origin_y] != CELL_BLOCK && random == 1)
            return DIR_RIGHT;
        if (map->cells[origin_x][(origin_y + 1 <= map->height - 1) ? origin_y + 1 : 0] != CELL_BLOCK && random == 2)
            return DIR_DOWN;
        if (map->cells[(origin_x - 1 >= 0) ? origin_x - 1 : map->width - 1][origin_y] != CELL_BLOCK && random == 3)
            return DIR_LEFT;
        if (map->cells[origin_x][(origin_y - 1 >= 0) ? origin_y - 1 : map->height - 1] != CELL_BLOCK && random == 4)
            return DIR_UP;
        return DIR_NONE;
    }


    long int i, j, counter = 0;
    long int queuex[map->width * map->height];
    long int queuey[map->width * map->height];
    int flag[map->width][map->height];
    long int prevx[map->width][map->height];
    long int prevy[map->width][map->height];

    for (i = 0; i < map->width; i++) {
        for (j = 0; j < map->height; j++) {
            prevx[i][j] = -1;
            prevy[i][j] = -1;
            flag[i][j] = 0;
        }
    }

    for (i = 0; i < map->width * map->height; i++) {
        queuex[i] = 0;
        queuey[i] = 0;
    }

    flag[origin_x][origin_y] = 1;

    if (origin_x != 0) {
        if (map->cells[origin_x - 1][origin_y] != CELL_BLOCK) {
            queuex[counter] = origin_x - 1;
            queuey[counter++] = origin_y;
        }
    }
    else {
        if (map->cells[map->width - 1][origin_y] != CELL_BLOCK) {
            queuex[counter] = map->width - 1;
            queuey[counter++] = origin_y;
        }
    }
    if (origin_x + 1 != map->width) {
        if (map->cells[origin_x + 1][origin_y] != CELL_BLOCK) {
            queuex[counter] = origin_x + 1;
            queuey[counter++] = origin_y;
        }
    }
    else {
        if (map->cells[0][origin_y] != CELL_BLOCK) {
            queuex[counter] = 0;
            queuey[counter++] = origin_y;
        }
    }
    if (origin_y != 0) {
        if (map->cells[origin_x][origin_y - 1] != CELL_BLOCK) {
            queuex[counter] = origin_x;
            queuey[counter++] = origin_y - 1;
        }
    }
    else {
        if (map->cells[origin_x][map->height - 1] != CELL_BLOCK) {
            queuex[counter] = origin_x;
            queuey[counter++] = map->height - 1;
        }
    }
    if (origin_y + 1 != map->height) {
        if (map->cells[origin_x][origin_y + 1] != CELL_BLOCK) {
            queuex[counter] = origin_x;
            queuey[counter++] = origin_y + 1;
        }
    }
    else {
        if (map->cells[origin_x][0] != CELL_BLOCK) {
            queuex[counter] = origin_x;
            queuey[counter++] = 0;
        }
    }

    long int counter2 = 1;

    while (counter2 != 0) {
        if (queuex[0] > 0) {
            if (map->cells[queuex[0] - 1][queuey[0]] != CELL_BLOCK && flag[queuex[0] - 1][queuey[0]] == 0) {
                prevx[queuex[0] - 1][queuey[0]] = queuex[0];
                prevy[queuex[0] - 1][queuey[0]] = queuey[0];
                flag[queuex[0] - 1][queuey[0]] = 1;
                queuex[counter] = queuex[0] - 1;
                queuey[counter++] = queuey[0];
            }
        }
        else {
            if (map->cells[map->width - 1][queuey[0]] != CELL_BLOCK && flag[map->width - 1][queuey[0]] == 0) {
                prevx[map->width - 1][queuey[0]] = queuex[0];
                prevy[map->width - 1][queuey[0]] = queuey[0];
                flag[map->width - 1][queuey[0]] = 1;
                queuex[counter] = map->width - 1;
                queuey[counter++] = queuey[0];
            }
        }

        if (queuex[0] + 1 != map->width) {
            if (map->cells[queuex[0] + 1][queuey[0]] != CELL_BLOCK && flag[queuex[0] + 1][queuey[0]] == 0) {
                prevx[queuex[0] + 1][queuey[0]] = queuex[0];
                prevy[queuex[0] + 1][queuey[0]] = queuey[0];
                flag[queuex[0] + 1][queuey[0]] = 1;
                queuex[counter] = queuex[0] + 1;
                queuey[counter++] = queuey[0];
            }
        }
        else {
            if (map->cells[0][queuey[0]] != CELL_BLOCK && flag[0][queuey[0]] == 0) {
                prevx[0][queuey[0]] = queuex[0];
                prevy[0][queuey[0]] = queuey[0];
                flag[0][queuey[0]] = 1;
                queuex[counter] = 0;
                queuey[counter++] = queuey[0];
            }
        }
        if (queuey[0] >= 0) {
            if (map->cells[queuex[0]][queuey[0] - 1] != CELL_BLOCK && flag[queuex[0]][queuey[0] - 1] == 0) {
                prevx[queuex[0]][queuey[0] - 1] = queuex[0];
                prevy[queuex[0]][queuey[0] - 1] = queuey[0];
                flag[queuex[0]][queuey[0] - 1] = 1;
                queuex[counter] = queuex[0];
                queuey[counter++] = queuey[0] - 1;
            }
        }
        else {
            if (map->cells[queuex[0]][map->height - 1] != CELL_BLOCK && flag[queuex[0]][map->height - 1] == 0) {
                prevx[queuex[0]][map->height - 1] = queuex[0];
                prevy[queuex[0]][map->height - 1] = queuey[0];
                flag[queuex[0]][map->height - 1] = 1;
                queuex[counter] = queuex[0];
                queuey[counter++] = map->height - 1;
            }
        }
        if (queuey[0] + 1 != map->height) {
            if (map->cells[queuex[0]][queuey[0] + 1] != CELL_BLOCK && flag[queuex[0]][queuey[0] + 1] == 0) {
                prevx[queuex[0]][queuey[0] + 1] = queuex[0];
                prevy[queuex[0]][queuey[0] + 1] = queuey[0];
                flag[queuex[0]][queuey[0] + 1] = 1;
                queuex[counter] = queuex[0];
                queuey[counter] = queuey[0] + 1;
            }
        }
        else {
            if (map->cells[queuex[0]][0] != CELL_BLOCK && flag[queuex[0]][0] == 0) {
                prevx[queuex[0]][0] = queuex[0];
                prevy[queuex[0]][0] = queuey[0];
                flag[queuex[0]][0] = 1;
                queuex[counter] = queuex[0];
                queuey[counter] = 0;
            }
        }
        for (i = 0; i < map->width * map->height - 1; i++) {
            queuex[i] = queuex[i + 1];
            queuey[i] = queuey[i + 1];
        }

        counter2 = 0;

        for (i = 0; i < map->height * map->width; i++) {
            if (queuex[i] != 0 || queuey[i] != 0)
                counter2++;
            if (counter2 != 0)
                break;
        }
    }

    long int tempx = prevx[dest_x][dest_y];
    long int tempy = prevy[dest_x][dest_y];

    while (tempx >= -1 && tempx <= map->width * map->height && tempy >= -1 && tempy <= map->width * map->height && prevx[tempx][tempy] != -1 && prevy[tempx][tempy] != -1) {
        long int temp = tempx;
        if (tempx == (origin_x - 1 >= 0 ? origin_x - 1 : map->width - 1) && tempy == origin_y)
            return DIR_LEFT;
        if (tempx == (origin_x + 1 <= map->width - 1 ? origin_x + 1 : 0) && tempy == origin_y)
            return DIR_RIGHT;
        if (tempx == origin_x && tempy == (origin_y + 1 <= map->height - 1 ? origin_y + 1: 0))
            return DIR_DOWN;
        if (tempx == origin_x && tempy == (origin_y - 1 >= 0 ? origin_y - 1 : map->height - 1))
            return DIR_UP;
        tempx = prevx[tempx][tempy];
        tempy = prevy[temp][tempy];
    }
    return DIR_NONE;
}


Direction decideGhost(const Map* map, Ghost* ghost, Pacman *pacman, Ghost *blinky) {
    if (ghost->type == BLINKY) {
        if (blinky->blue == true)
            return BFS(map, (int)blinky->x, (int) blinky->y, blinky->startX, blinky->startY);
        return BFS(map, (int) (blinky->x), (int) blinky->y,(int) pacman->x, (int) pacman->y);
    }

    if (ghost->type == INKY) {
        if (ghost->blue == true)
            return BFS(map, (int)ghost->x, (int) ghost->y, ghost->startX, ghost->startY);
        int destx = ((int) pacman->x + 2 + ((int) pacman->x + 2 - (int) blinky->x)) % map->width;
        int desty = ((int) pacman->y + 2 + ((int) pacman->y + 2 - (int) blinky->y)) % map->height;
        if (map->cells[destx][desty] == CELL_BLOCK) {
            if (map->cells[destx + 1][desty] != CELL_BLOCK && destx + 1 != map->width)
                return BFS(map, (int) ghost->x, (int) ghost->y, destx + 1, desty);
            if (map->cells[destx][desty + 1] != CELL_BLOCK && desty + 1 != map->height)
                return BFS(map, (int) ghost->x, (int) ghost->y, destx, desty + 1);
            if (map->cells[destx + 1][desty + 1] != CELL_BLOCK && destx + 1 != map->width && desty + 1 != map->height)
                return BFS(map, (int) ghost->x, (int) ghost->y, destx + 1, desty + 1);
            if (map->cells[destx - 1][desty] != CELL_BLOCK && destx != 0)
                return BFS(map, (int) ghost->x, (int) ghost->y, destx - 1, desty);
            if (map->cells[destx][desty - 1] != CELL_BLOCK && desty != 0)
                return BFS(map, (int) ghost->x, (int) ghost->y, destx, desty - 1);
            if (map->cells[destx - 1][desty - 1] != CELL_BLOCK && destx != 0 && desty != 0)
                return BFS(map, (int) ghost->x, (int) ghost->y, destx - 1, desty - 1);
        }
        return BFS(map, (int) ghost->x, (int) ghost->y, destx, desty);
    }

    if (ghost->type == CLYDE) {
        return DIR_NONE;
    }

    if (ghost->type == PINKY) {
        return DIR_NONE;
    }

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
