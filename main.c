#include <stdio.h>

#define LOG(x) printf("%s = %d\n", #x, x)

struct pacman{
    int direction;
    int lives;
    int x_start;
    int y_start;
    int x_now;
    int y_now;
};

struct ghost {
    int direction;
    int mode;
    int defensive_time;
    int x_start;
    int y_start;
    int x_now;
    int y_now;
};

void pacman_place_finder (int n, int m, char page[n][m], struct pacman *pacman);
void trace_points(int n, int m, char page[n][m], int pacman_x_now, int pacman_y_now, int *points, int *pineapple_counter, int *cheese_counter);
void check_ghosts(struct pacman *pacman, struct ghost *blinky, struct ghost *pinky, struct ghost *clyde, struct ghost *inky, int *points);

int main () {
    int n, m, counter1, counter2, minute, second, points, cheese_counter = 0, pineapple_counter = 0;
    struct pacman pacman;
    struct ghost blinky;
    struct ghost pinky;
    struct ghost clyde;
    struct ghost inky;

    scanf("%d %d", &n, &m);
    char temp[m];
    char page[n][m];
    for (counter1 = 0; counter1 < n; counter1++) {
        scanf("%s", temp);
        for (counter2 = 0; counter2 < m; counter2++) {
            page[counter1][counter2] = temp[counter2];
            if (page[counter1][counter2] == '*')
                cheese_counter++;
            if (page[counter1][counter2] == 'O')
                pineapple_counter++;
        }
    }
    scanf("%d:%d %d", &minute, &second, &points);

    scanf("%*s %d %d (%d,%d) (%d,%d)", &pacman.direction, &pacman.lives, &pacman.x_start, &pacman.y_start, &pacman.x_now, &pacman.y_now);
    scanf("%*s %d %d ",  &blinky.direction, &blinky.mode);
    if (blinky.mode == 0)
        scanf("%d ", &blinky.defensive_time);
    scanf("(%d,%d) (%d,%d)", &blinky.x_start, &blinky.y_start, &blinky.x_now, &blinky.y_now);

    scanf("%*s %d %d ",  &pinky.direction, &pinky.mode);
    if (pinky.mode == 0)
        scanf("%d ", &pinky.defensive_time);
    scanf("(%d,%d) (%d,%d)", &pinky.x_start, &pinky.y_start, &pinky.x_now, &pinky.y_now);

    scanf("%*s %d %d ",  &clyde.direction, &clyde.mode);
    if (clyde.mode == 0)
        scanf("%d ", &clyde.defensive_time);
    scanf("(%d,%d) (%d,%d)", &clyde.x_start, &clyde.y_start, &clyde.x_now, &clyde.y_now);

    scanf("%*s %d %d ",  &inky.direction, &inky.mode);
    if (inky.mode == 0)
        scanf("%d ", &inky.defensive_time);
    scanf("(%d,%d) (%d,%d)", &inky.x_start, &inky.y_start, &inky.x_now, &inky.y_now);

    pacman_place_finder(n, m, page, &pacman);
    trace_points(n, m, page, pacman.x_now, pacman.y_now, &points, &pineapple_counter, &cheese_counter);

    if (page[pacman.x_now][pacman.y_now] == 'O')
        blinky.mode = pinky.mode = clyde.mode = inky.mode = 0;

    check_ghosts(&pacman, &blinky, &pinky, &clyde, &inky, &points);

    printf("(%d,%d)\n%d\n", pacman.x_now, pacman.y_now, points);
    if (cheese_counter == 0 && pineapple_counter == 0 && pacman.lives != 0)
        printf("Yes");
    else
        printf("No");

    return 0;
}

void pacman_place_finder (int n, int m, char page[n][m], struct pacman *pacman) {

    int temp_x = pacman->x_now;
    int temp_y = pacman->y_now;

    switch (pacman->direction) {
        case 1: pacman->x_now -= 1; break;
        case 2: pacman->y_now += 1; break;
        case 3: pacman->x_now += 1; break;
        case 4: pacman->y_now -= 1; break;
    }

    if (pacman->y_now == m)
        pacman->y_now = 0;
    if (pacman->y_now == -1)
        pacman->y_now = m - 1;
    if (pacman->x_now == n)
        pacman->x_now = 0;
    if (pacman->x_now == -1)
        pacman->x_now = n-1;

    if(page[pacman->x_now][pacman->y_now] == '#') {
        pacman->x_now = temp_x;
        pacman->y_now = temp_y;
    }
}

void trace_points(int n, int m, char page[n][m], int pacman_x_now, int pacman_y_now, int *points, int *pineapple_counter, int *cheese_counter) {
    if (page[pacman_x_now][pacman_y_now] == '*') {
        *points += 1;
        *cheese_counter -= 1;
    }
    if (page[pacman_x_now][pacman_y_now] == '^')
        *points += 20;
    if (page[pacman_x_now][pacman_y_now] == 'O') {
        *pineapple_counter -= 1;
    }
}

void check_ghosts(struct pacman *pacman, struct ghost *blinky, struct ghost *pinky, struct ghost *clyde, struct ghost *inky, int *points) {


    if (pacman->x_now == blinky->x_now && pacman->y_now == blinky->y_now && blinky->mode == 0) {
        blinky->x_now = blinky->x_start;
        blinky->y_now = blinky->y_start;
        *points += 50;
    }

    if (pacman->x_now == pinky->x_now && pacman->y_now == pinky->y_now && pinky->mode == 0) {
        pinky->x_now = pinky->x_start;
        pinky->y_now = pinky->y_start;
        *points += 50;
    }


    if (pacman->x_now == clyde->x_now && pacman->y_now == clyde->y_now && clyde->mode == 0) {
        clyde->x_now = clyde->x_start;
        clyde->y_now = clyde->y_start;
        *points += 50;
    }

    if (pacman->x_now == inky->x_now && pacman->y_now == inky->y_now && inky->mode == 0) {
        inky->x_now = inky->x_start;
        inky->y_now = inky->y_start;
        *points += 50;
    }

    if (pacman->x_now == blinky->x_now && pacman->y_now == blinky->y_now && blinky->mode == 1) {
        pacman->x_now = pacman->x_start;
        pacman->y_now = pacman->y_start;
        pacman->lives -= 1;
    }


    if (pacman->x_now == pinky->x_now && pacman->y_now == pinky->y_now && pinky->mode == 1) {
        pacman->x_now = pacman->x_start;
        pacman->y_now = pacman->y_start;
        pacman->lives -= 1;
    }


    if (pacman->x_now == clyde->x_now && pacman->y_now == clyde->y_now && clyde->mode == 1) {
        pacman->x_now = pacman->x_start;
        pacman->y_now = pacman->y_start;
        pacman->lives -= 1;
    }


    if (pacman->x_now == inky->x_now && pacman->y_now == inky->y_now && inky->mode == 1) {
        pacman->x_now = pacman->x_start;
        pacman->y_now = pacman->y_start;
        pacman->lives -= 1;
    }

}


