#include "snake.h"
#include "board.h"
#include "constants.h"
#include <stdio.h>

void main() {
    init_board();
    struct Snake snake = create_snake();
    add_snake_to_board(snake.head);
    place_random_food();

    for (int i = 0; i < 9; i++) {
        move(&snake.head, snake.direction_x, snake.direction_y);
    }

    set_direction(&snake, DIRECTION_DOWN);

    for (int i = 0; i < 7; i++) {
        move(&snake.head, snake.direction_x, snake.direction_y);
    }

    print_board();
}