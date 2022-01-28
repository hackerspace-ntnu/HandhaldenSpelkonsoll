#include "snake.h"
#include "board.h"
#include "constants.h"
#include <stdio.h>

void main() {
    int count_food = 0;
    init_board();
    struct Snake snake = create_snake();
    add_snake_to_board(snake.head);
    place_random_food(&count_food);

    for (int i = 0; i < 2; i++) {
        move(&snake.head, snake.direction_x, snake.direction_y, &count_food);
    }

    struct Body* segment = snake.head->next->next->next;

    split_snake(&segment, &count_food);

    move(&snake.head, snake.direction_x, snake.direction_y, &count_food);

    set_direction(&snake, DIRECTION_DOWN);

    move(&snake.head, snake.direction_x, snake.direction_y, &count_food);

    set_direction(&snake, DIRECTION_LEFT);

    move(&snake.head, snake.direction_x, snake.direction_y, &count_food);
    move(&snake.head, snake.direction_x, snake.direction_y, &count_food);
    move(&snake.head, snake.direction_x, snake.direction_y, &count_food);
    move(&snake.head, snake.direction_x, snake.direction_y, &count_food);

    set_direction(&snake, DIRECTION_UP);

    move(&snake.head, snake.direction_x, snake.direction_y, &count_food);

    set_direction(&snake, DIRECTION_LEFT);

    for (int i = 0; i <= 1; i++) {
        move(&snake.head, snake.direction_x, snake.direction_y, &count_food);
    }

    set_direction(&snake, DIRECTION_DOWN);

    for (int i = 0; i <= 2; i++) {
        move(&snake.head, snake.direction_x, snake.direction_y, &count_food);
    }

    set_direction(&snake, DIRECTION_RIGHT);
    
    for (int i = 0; i <= 8; i++) {
        move(&snake.head, snake.direction_x, snake.direction_y, &count_food);
    }

    print_board();
}