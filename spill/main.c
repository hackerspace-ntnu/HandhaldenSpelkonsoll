#include "snake.h"
#include "board.h"
#include "constants.h"
#include <stdio.h>

void main() {
    int board[BOARD_HEIGHT][BOARD_WIDTH];
    int count_food = 0;
    init_board();

    int coords1[][2] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}};
    int coords2[][2] = {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}};
    int length_coords1 = sizeof coords1 / sizeof coords1[0];
    int length_coords2 = sizeof coords2 / sizeof coords2[0];

    struct Snake snake1 = create_snake(length_coords1, coords1);
    struct Snake snake2 = create_snake(length_coords2, coords2);
    add_snake_to_board(snake1.head);
    add_snake_to_board(snake2.head);

    place_random_food(&count_food);

    printf("\n");

    for (int i = 0; i < 3; i++) {
        move(&snake1, &snake1.head, snake1.direction_x, snake1.direction_y, &count_food);
    }

    set_direction(&snake2, DIRECTION_UP);
    for (int i = 0; i < 2; i++) {
        move(&snake2, &snake2.head, snake2.direction_x, snake2.direction_y, &count_food);
    }
    // set_direction(&snake2, DIRECTION_LEFT);
    
    // for (int i = 0; i < 2; i++) {
    //     move(&snake2, &snake2.head, snake2.direction_x, snake2.direction_y, &count_food);
    // }

    // set_direction(&snake2, DIRECTION_UP);

    // for (int i = 0; i < 2; i++) {
    //     move(&snake2, &snake2.head, snake2.direction_x, snake2.direction_y, &count_food);
    // }

    // for (int i = 0; i < 3; i++) {
    //     move(&snake2, &snake2.head, snake2.direction_x, snake2.direction_y, &count_food);
    // }

    print_board();
}