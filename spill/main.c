#include "snake.h"
#include "board.h"
#include <stdio.h>

void main() {
    init_board();
    struct Snake snake = create_snake();
    add_snake_to_board(snake.head);
    place_random_food();

    short int next_x = snake.head->x + snake.direction_x;
    short int next_y = snake.head->y + snake.direction_y;

    move(&snake.head, snake.direction_x, snake.direction_y, get_square_value(next_x, next_y) == BLOCK_FOOD);
}