#ifndef __INPUT_H
#define __INPUT_H

#define MOVE_ACTION_MASK 0b001110

typedef enum {
    ACTION_LEFT = 0b001110,
    ACTION_RIGHT = 0b000110,
    ACTION_UP = 0b000010,
    ACTION_DOWN = 0b001010,

    // you have nothing to do with other actions, simply ignore them.
    ACTION_PAUSE = 0b010000,
    ACTION_IDLE = 0b000001,
    ACTION_EXIT = 0b100000
} Action;

#endif