#include <stdio.h>
#include <stdlib.h>
#include "SDL2_gfxPrimitives.h"
#include <math.h>
#include <time.h>
#include "src/game.h"
#include "src/physics.h"
#include "src/map.h"

#define LOG(x) printf("%s = %f\n", #x, x)

int main() {
    srand(time(NULL));

    Map map;
    Game game;
    Pacman pacman;
    Ghost ghost[4];
    Action action;
    Direction dir;

    initiateGame("res/map.txt", &map, &game, &pacman, &ghost);

    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf ("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("PacMan", 100, 100, map.width * 100, map.height * 100 + 150, SDL_WINDOW_OPENGL);
    if (window == NULL)
    {
        printf ("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        return 2;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        printf ("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        return 3;
    }

    long long int cycle = 0;
    int quit = 0;
    int play = 0;
    int delay = 10;
    int pause = 0;
    int point_flag = 0;
    long long int point_temp = 123456;
    int pointx = 0;
    int pointy = 0;
    int lastpoint = 0;
    int i, j;
    int degree = 45, temp_degree = 45;
    int degree2 = 45;
    int degree_flag = 0;
    int degree_flag2 = 0;
    int end_of_game = 0;
    int won = 0;
    char buffer[100];
    long long int temp_cycle = 1;
    double x = -100, y = 600;

    SDL_Event e;

    while (!quit)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) {
                action = ACTION_EXIT;
                quit = 1;
            }
            else if( e.type == SDL_KEYDOWN ) {
                switch( e.key.keysym.sym ) {
                    case SDLK_UP:
                            action = ACTION_UP;
                        break;
                    case SDLK_DOWN:
                            action = ACTION_DOWN;
                        break;
                    case SDLK_LEFT:
                            action = ACTION_LEFT;
                        break;
                    case SDLK_RIGHT:
                            action = ACTION_RIGHT;
                        break;
                    case SDLK_q:
                        action = ACTION_EXIT;
                        quit = 1;
                        break;
                    case SDLK_p:
                        action = ACTION_PAUSE;
                        if (pause == 1)
                            pause = 0;
                        else
                            pause = 1;
                        break;
                    case SDLK_s:
                        play = 1;
                        break;
                    default:
                        action = ACTION_IDLE;
                        break;
                }
            }
        }

        if (play == 0) {
            boxColor(renderer, 0, 0, map.width * 100, map.height * 100 + 150, 0xFF000000);
            SDL_RenderSetScale(renderer, 3, 3);
            stringColor(renderer, map.width * 12, map. height * 5, "PacMan!", 0xFFFFFFFF);
            SDL_RenderSetScale(renderer, 1, 1);
            SDL_RenderSetScale(renderer, 2, 2);
            stringColor(renderer, map.width * 15, map. height * 20, "By: Arshia Moghimi", 0xFFFFFFFF);
            SDL_RenderSetScale(renderer, 1, 1);
            SDL_RenderSetScale(renderer, 2, 2);
            stringColor(renderer, map.width * 11, map. height * 30, "Press 's' to start playing.", 0xFFFFFFFF);
            SDL_RenderSetScale(renderer, 1, 1);
            SDL_RenderSetScale(renderer, 2, 2);
            stringColor(renderer, map.width * 15, map. height * 40, "Press 'q' to quit.", 0xFFFFFFFF);
            SDL_RenderSetScale(renderer, 1, 1);
            if (degree2 == 45 || degree2 == 0)
                degree_flag2 = degree_flag2 == 1 ? 0 : 1;
            filledPieColor(renderer, x, y, 50, degree2, -(degree_flag2 == 1 ? degree2-- : degree2++), 0xFF00FFFF);
            x = x + 2;
            filledPieColor(renderer, 100,100, 36, 180, 0, 0xFF0000FF);
            boxColor(renderer, 64,100, 136,146, 0xFF0000FF);
            filledPieColor(renderer, 76, 146, 12, 180, 0, 0xFF000000);
            filledPieColor(renderer, 100, 146, 12, 180, 0, 0xFF000000);
            filledPieColor(renderer, 124, 146, 12, 180, 0, 0xFF000000);
            filledCircleColor(renderer, 85, 90, 10, 0xFFFFFFFF);
            filledCircleColor(renderer, 115, 90, 10, 0xFFFFFFFF);
            filledCircleColor(renderer, 85, 90, 5, 0xFF000000);
            filledCircleColor(renderer, 115, 90, 5, 0xFF000000);

            filledCircleColor(renderer, 700, 100, 15, 0xFF3030FF);
            filledCircleColor(renderer, 660, 100, 15, 0xFF3030FF);
            thickLineColor(renderer, 680, 50 , 700, 85, 3, 0xFF00FF00);
            thickLineColor(renderer, 680, 50 , 660, 85, 3, 0xFF00FF00);

            SDL_RenderPresent(renderer);
            SDL_Delay(10);
        }
        else if (pause == 0 && play == 1) {
            SDL_RenderClear(renderer);

            //Undermap menu
            boxColor(renderer, 0, map.height * 100, map.width * 100, map.height * 100 + 150, 0xFF606060);
            SDL_RenderSetScale(renderer, 2, 2);
            stringColor(renderer, 10, map.height * 50 + 10, "Lives:", 0xFFFFFFFF);
            SDL_RenderSetScale(renderer, 1, 1);
            for (i = 1; i <= pacman.health; ++i) {
                    filledPieColor(renderer, 50 * i + 100, map.height * 100 + 25, 20, 45, -45, 0xFF00FFFF);
                    filledCircleColor(renderer, 50 * i + 97, map.height * 100 + 15, 3, 0xFF000000);
            }
            sprintf(buffer, "Score: %d", game.score);
            SDL_RenderSetScale(renderer, 2, 2);
            stringColor(renderer, 10, map.height * 50 + 50, buffer, 0xFFFFFFFF);
            sprintf(buffer, "Timer: %d", cycle);
            stringColor(renderer, map.width * 25, map.height * 50 + 10, buffer, 0xFFFFFFFF);
            stringColor(renderer, map.width * 25, map.height * 50 + 30, "Press 'q' to quit.", 0xFFFFFFFF);
            stringColor(renderer, map.width * 25, map.height * 50 + 50, "Press 'p' to pause.", 0xFFFFFFFF);
            SDL_RenderSetScale(renderer, 1, 1);
            //End of undermap menu

            for (i = 0; i < map.width; i++) {
                for (j = 0; j < map.height; j++) {
                    switch (map.cells[i][j]) {
                        case CELL_BLOCK:
                            boxColor(renderer, i * 100, j * 100, i * 100 + 100, j * 100 + 100, 0xFFFFFFFF);
                            break;
                        case CELL_CHEESE:
                            filledCircleColor(renderer, i * 100 + 50, j * 100 + 50, 10, 0xFF00FFFF);
                            break;
                        case CELL_CHERRY:
                            filledCircleColor(renderer, i * 100 + 70, j * 100 + 70, 15, 0xFF3030FF);
                            filledCircleColor(renderer, i * 100 + 30, j * 100 + 70, 15, 0xFF3030FF);
                            thickLineColor(renderer, i * 100 + 50, j * 100 + 20, i * 100 + 70, j * 100 + 55, 3, 0xFF00FF00);
                            thickLineColor(renderer, i * 100 + 50, j * 100 + 20, i * 100 + 30, j * 100 + 55, 3, 0xFF00FF00);
                            break;
                        case CELL_PINEAPPLE:
                            filledCircleColor(renderer, i * 100 + 50, j * 100 + 70, 25, 0xFF0060A7);
                            filledCircleColor(renderer, i * 100 + 50, j * 100 + 60, 22, 0xFF0060A7);
                            filledCircleColor(renderer, i * 100 + 50, j * 100 + 50, 20, 0xFF0060A7);
                            filledCircleColor(renderer, i * 100 + 50, j * 100 + 40, 20, 0xFF0060A7);
                            filledCircleColor(renderer, i * 100 + 40, j * 100 + 40, 2, 0xFF00FFFF);
                            filledCircleColor(renderer, i * 100 + 40, j * 100 + 82, 2, 0xFF00FFFF);
                            filledCircleColor(renderer, i * 100 + 55, j * 100 + 37, 2, 0xFF00FFFF);
                            filledCircleColor(renderer, i * 100 + 55, j * 100 + 75, 2, 0xFF00FFFF);

                            arcColor(renderer, i * 100 + 40, j * 100 + 20, 10, 200, 0, 0xFF00FF00);
                            arcColor(renderer, i * 100 + 38, j * 100 + 18, 10, 200, 0, 0xFF00FF00);
                            arcColor(renderer, i * 100 + 60, j * 100 + 20, 10, 180, 340, 0xFF00FF00);
                            arcColor(renderer, i * 100 + 58, j * 100 + 18, 10, 180, 340, 0xFF00FF00);
                            thickLineColor(renderer, i * 100 + 50, j * 100 + 20, i * 100 + 45, j * 100 + 7, 3, 0xFF00FF00);
                            thickLineColor(renderer, (i * 100 + 50), j * 100 + 20, i * 100 + 55, j * 100 + 7, 3, 0xFF00FF00);
                            break;
                    }
                }
            }
LOG(pacman.y);
            LOG(pacman.x);

            //pacman
            if (fabs(pacman.x - (float) map.width) < 0.5 || pacman.x > map.width - 1)
                pacman.x = 0;
            if (fabs(pacman.y - (float)map.height) < 0.5 || pacman.y > map.height - 1)
                pacman.y = 0;
            if (pacman.x < 0)
                pacman.x = map.width - 1;
            if (pacman.y < 0)
                pacman.y = map.height - 1;
            double x = pacman.x, y = pacman.y;
            Direction temp;
            if (decidePacman(&map, &pacman, action) == DIR_UP) {
                temp = DIR_UP;
                if (degree == 45 || degree == 0)
                    degree_flag = degree_flag == 1 ? 0 : 1;
                filledPieColor(renderer, pacman.x * 100 + 50, pacman.y * 100 + 50, 50, 270 + degree, 270 - (degree_flag == 1 ? ((degree = degree - 9) + 10) : (degree = degree + 9) + 10), 0xFF00FFFF);
                pacman.y = pacman.y - 1;
            }
            else if (decidePacman(&map, &pacman, action) == DIR_DOWN) {
                temp = DIR_DOWN;
                if (degree == 45 || degree == 0)
                    degree_flag = degree_flag == 1 ? 0 : 1;
                filledPieColor(renderer, pacman.x * 100 + 50, pacman.y * 100 + 50, 50, 90 + degree, 90 - (degree_flag == 1 ? ((degree = degree - 9) + 10) : (degree = degree + 9) + 10), 0xFF00FFFF);
                pacman.y = pacman.y + 1;
            }
            else if (decidePacman(&map, &pacman, action) == DIR_LEFT) {
                temp = DIR_LEFT;
                if (degree == 45 || degree == 0)
                    degree_flag = degree_flag == 1 ? 0 : 1;
                filledPieColor(renderer, pacman.x * 100 + 50, pacman.y * 100 + 50, 50, 180 + degree, 180 - (degree_flag == 1 ? ((degree = degree - 9) + 10) : (degree = degree + 9) + 10), 0xFF00FFFF);
                pacman.x = pacman.x - 1;
            }
            else if (decidePacman(&map, &pacman, action) == DIR_RIGHT) {
                temp = DIR_RIGHT;
                if (degree == 45 || degree == 0)
                    degree_flag = degree_flag == 1 ? 0 : 1;
                filledPieColor(renderer, pacman.x * 100 + 50, pacman.y * 100 + 50, 50, degree, -(degree_flag == 1 ? ((degree = degree - 9) + 10) : (degree = degree + 9) + 10), 0xFF00FFFF);
                pacman.x = pacman.x + 1;
            }
            else {
                pacman.x = x;
                pacman.y = y;
                switch (temp) {
                    case DIR_UP:
                        filledPieColor(renderer, pacman.x * 100 + 50, pacman.y * 100 + 50, 50, 270 + degree + 1, 270 - degree - 1, 0xFF00FFFF);
                        break;
                    case DIR_DOWN:
                        filledPieColor(renderer, pacman.x * 100 + 50, pacman.y * 100 + 50, 50, 90 + degree + 1, 90 - degree - 1, 0xFF00FFFF);
                        break;
                    case DIR_RIGHT:
                        filledPieColor(renderer, pacman.x * 100 + 50, pacman.y * 100 + 50, 50, degree + 1, -degree - 1, 0xFF00FFFF);
                        break;
                    case DIR_LEFT:
                        filledPieColor(renderer, pacman.x * 100 + 50, pacman.y * 100 + 50, 50, 180 + degree + 1, 180 - degree - 1, 0xFF00FFFF);
                        break;
                }
            }
            //end of pacman

            //ghosts
            int red[4] = {255, 128, 190, 60}, green[4] = {0, 60, 190, 60}, blue[4] = {0, 60, 190, 128};
            for (i = 0; i < 4; i++) {
                if (fabs(ghost[i].x - (float) map.width) < 0.5 || ghost[i].x > map.width - 1)
                    ghost[i].x = 0;
                if (fabs(ghost[i].y - (float)map.height) < 0.5 || ghost[i].y > map.height - 1)
                    ghost[i].y = 0;
                if (ghost[i].x < 0)
                    ghost[i].x = map.width - 1;
                if (ghost[i].y < 0)
                    ghost[i].y = map.height - 1;
                if(decideGhost(&map, &ghost[i], &pacman, &ghost[0]) == DIR_RIGHT) {
                    ghost[i].x += 1;
                }
                if(decideGhost(&map, &ghost[i], &pacman, &ghost[0]) == DIR_UP) {
                    ghost[i].y -= 1;
                }
                if(decideGhost(&map, &ghost[i], &pacman, &ghost[0]) == DIR_DOWN) {
                    ghost[i].y += 1;
                }
                if(decideGhost(&map, &ghost[i], &pacman, &ghost[0]) == DIR_LEFT) {
                    ghost[i].x -= 1;
                }
                if (ghost[i].blue  == true) {
                    blue[i] = 255;
                    green[i] = 50;
                    red[i] = 50;
                }
                else {
                    red[0] = 255;
                    red[1] = 128;
                    red[2] = 190;
                    red[3] = 60;
                    green[0] = 0;
                    green[1] = 60;
                    green[2] = 190;
                    green[3] = 60;
                    blue[0] = 0;
                    blue[1] = 60;
                    blue[2] = 190;
                    blue[3] = 128;
                }

                filledPieRGBA(renderer, ghost[i].x * 100 + 50, ghost[i].y * 100 + 50, 36, 180, 0, red[i], green[i], blue[i], 255);
                boxRGBA(renderer, ghost[i].x * 100 + 14, ghost[i].y * 100 + 50, ghost[i].x * 100 + 86, ghost[i].y * 100 + 96, red[i], green[i], blue[i], 255);
                filledPieColor(renderer, ghost[i].x * 100 + 26, ghost[i].y * 100 + 96, 12, 180, 0, 0xFF000000);
                filledPieColor(renderer, ghost[i].x * 100 + 50, ghost[i].y * 100 + 96, 12, 180, 0, 0xFF000000);
                filledPieColor(renderer, ghost[i].x * 100 + 74, ghost[i].y * 100 + 96, 12, 180, 0, 0xFF000000);
                filledCircleColor(renderer, ghost[i].x * 100 + 35, ghost[i].y * 100 + 40, 10, 0xFFFFFFFF);
                filledCircleColor(renderer, ghost[i].x * 100 + 65, ghost[i].y * 100 + 40, 10, 0xFFFFFFFF);
                filledCircleColor(renderer, ghost[i].x * 100 + 35, ghost[i].y * 100 + 40, 5, 0xFF000000);
                filledCircleColor(renderer, ghost[i].x * 100 + 65, ghost[i].y * 100 + 40, 5, 0xFF000000);

            }
            //end of ghosts

            checkEatables(&map, &game, &pacman, &ghost);
            if (game.cheeses == 0 && game.pineapples == 0)
                won = 1;
            for (i = 0; i < 4; i++) {
                checkGhostCollision(&pacman, &ghost[i]);
                checkGhostState(&ghost[i]);
            }

            SDL_RenderPresent(renderer);
            SDL_Delay(1000);
            cycle++;
            if (isGameFinished(&game, &pacman)) {
                end_of_game = 1;
                break;
            }
        }
        else if (pause == 1 && play == 1) {
            boxColor(renderer, 0, 0, map.width * 100, map.height * 100, 0x33000000);
            SDL_RenderSetScale(renderer, 2, 2);
            stringColor(renderer, map.width * 7, map.height * 25, "Paused! press 'p' to resume game.", 0xFFFFFFFF);
            SDL_RenderSetScale(renderer, 1, 1);
            SDL_RenderPresent(renderer);
            SDL_Delay(delay);
        }
    }
    if (won == 0 && end_of_game == 1) {
        SDL_RenderClear(renderer);
        boxColor(renderer, 0, 0, map.width * 100, map.height * 100, 0x33000000);
        SDL_RenderSetScale(renderer, 2, 2);
        stringColor(renderer, map.width * 7, map.height * 25, "Bad Luck. You have lost :(", 0xFFFFFFFF);
        SDL_RenderSetScale(renderer, 1, 1);
        SDL_RenderPresent(renderer);
        SDL_Delay(3000);
    }
    else if (won == 1 && end_of_game == 1) {
        SDL_RenderClear(renderer);
        boxColor(renderer, 0, 0, map.width * 100, map.height * 100, 0x33000000);
        SDL_RenderSetScale(renderer, 2, 2);
        stringColor(renderer, map.width * 7, map.height * 25, "Congratulations. You have WON :)", 0xFFFFFFFF);
        SDL_RenderSetScale(renderer, 1, 1);
        SDL_RenderPresent(renderer);
        SDL_Delay(3000);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}