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

    return 0;
}