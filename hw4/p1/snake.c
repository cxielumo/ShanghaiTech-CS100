#include "snake.h"

bool snakeInit(Snake *snake, int rows, int cols, size_t length) {
    /* TODO: Make a ring. Start in the middle, facing right.
     * On failure, free any nodes already made and leave an empty snake. */
    (void)rows;
    (void)cols;
    (void)length;
    *snake = (Snake){0};
    return false;
}

Coord snakeNextPosition(const Snake *snake, Direction requested) {
    /* TODO: Return the next head position. Do not change the snake.
     * Ignore a turn straight back when the snake has more than one node. */
    (void)snake;
    (void)requested;
    return (Coord){0};
}

bool snakeContains(const Snake *snake, Coord pos) {
    /* TODO: Check every node once. The ring does not end at NULL. */
    (void)snake;
    (void)pos;
    return false;
}

StepResult snakeStep(Snake *snake, Direction requested, bool grow) {
    /* TODO: Check the next position before changing the ring.
     * Reuse the tail on a normal move; add one node when growing.
     * A normal move may enter the old tail's cell. A growing move may not. */
    (void)snake;
    (void)requested;
    (void)grow;
    return STEP_NO_MEMORY;
}

void snakeDestroy(Snake *snake) {
    /* TODO: Free every node, then reset the snake. */
    *snake = (Snake){0};
}

unsigned int nextRandom(unsigned int seed) {
    /* TODO: Keep one static unsigned int state, initially RANDOM_INITIAL_SEED.
     * A positive seed resets it modulo RANDOM_MODULUS. Then take one
     * recurrence step and return the new state. Zero continues the sequence. */
    (void)seed;
    return 0;
}
