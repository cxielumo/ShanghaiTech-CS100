#include "snake.h"
#include <stdlib.h>

static Direction effectiveDirection(const Snake *snake, Direction requested) {
    if (requested < DIR_UP || requested >= DIRECTION_COUNT) {
        return snake->m_direction;
    }
    if (snake->m_length > 1 &&
        (requested + DIRECTION_COUNT / 2) % DIRECTION_COUNT == snake->m_direction) {
        return snake->m_direction;
    }
    return requested;
}

bool snakeInit(Snake *snake, int rows, int cols, size_t length) {
    *snake = (Snake){0};
    if (rows < MIN_BOARD_SIZE || cols < MIN_BOARD_SIZE || length == 0 ||
        length > (size_t)(cols - 2 * BOARD_WALL_THICKNESS)) {
        return false;
    }
    snake->m_rows = rows;
    snake->m_cols = cols;
    snake->m_direction = DIR_RIGHT;
    int headCol = cols / 2;
    if ((size_t)headCol < length) {
        headCol = (int)length;
    }
    for (size_t i = 0; i < length; ++i) {
        SnakeNode *node = malloc(sizeof(*node));
        if (node == NULL) {
            snakeDestroy(snake);
            return false;
        }
        node->m_pos = (Coord){rows / 2, headCol - (int)length + 1 + (int)i};
        if (snake->m_head == NULL) {
            node->m_next = node;
        } else {
            node->m_next = snake->m_head->m_next;
            snake->m_head->m_next = node;
        }
        snake->m_head = node;
        ++snake->m_length;
    }
    return true;
}

Coord snakeNextPosition(const Snake *snake, Direction requested) {
    Coord next = snake->m_head->m_pos;
    switch (effectiveDirection(snake, requested)) {
    case DIR_UP:
        --next.m_row;
        break;
    case DIR_RIGHT:
        ++next.m_col;
        break;
    case DIR_DOWN:
        ++next.m_row;
        break;
    case DIR_LEFT:
        --next.m_col;
        break;
    default:
        break;
    }
    return next;
}

bool snakeContains(const Snake *snake, Coord pos) {
    if (snake->m_head == NULL || snake->m_length == 0) {
        return false;
    }
    const SnakeNode *node = snake->m_head;
    do {
        if (node->m_pos.m_row == pos.m_row && node->m_pos.m_col == pos.m_col) {
            return true;
        }
        node = node->m_next;
    } while (node != snake->m_head);
    return false;
}

StepResult snakeStep(Snake *snake, Direction requested, bool grow) {
    Coord next = snakeNextPosition(snake, requested);
    if (next.m_row < BOARD_WALL_THICKNESS || next.m_row >= snake->m_rows - BOARD_WALL_THICKNESS ||
        next.m_col < BOARD_WALL_THICKNESS || next.m_col >= snake->m_cols - BOARD_WALL_THICKNESS) {
        return STEP_WALL;
    }
    SnakeNode *tail = snake->m_head->m_next;
    SnakeNode *node = tail;
    do {
        if ((grow || node != tail) && node->m_pos.m_row == next.m_row &&
            node->m_pos.m_col == next.m_col) {
            return STEP_SELF;
        }
        node = node->m_next;
    } while (node != tail);

    Direction direction = effectiveDirection(snake, requested);
    if (grow) {
        node = malloc(sizeof(*node));
        if (node == NULL) {
            return STEP_NO_MEMORY;
        }
        node->m_pos = next;
        node->m_next = tail;
        snake->m_head->m_next = node;
        snake->m_head = node;
        ++snake->m_length;
    } else {
        /* Rotating the head to the old tail preserves every ring link. */
        tail->m_pos = next;
        snake->m_head = tail;
    }
    snake->m_direction = direction;
    return STEP_OK;
}

void snakeDestroy(Snake *snake) {
    if (snake->m_head != NULL) {
        /* Break the ring so cleanup never follows a freed node. */
        SnakeNode *node = snake->m_head->m_next;
        snake->m_head->m_next = NULL;
        while (node != NULL) {
            SnakeNode *next = node->m_next;
            free(node);
            node = next;
        }
    }
    *snake = (Snake){0};
}

unsigned int nextRandom(unsigned int seed) {
    static unsigned int state = RANDOM_INITIAL_SEED;
    if (seed > 0) {
        state = seed % RANDOM_MODULUS;
    }
    state = (RANDOM_MULTIPLIER * state + RANDOM_INCREMENT) % RANDOM_MODULUS;
    return state;
}
