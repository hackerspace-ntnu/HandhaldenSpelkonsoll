#include "snake.h"
#include "board.h"
#include "constants.h"
#include <stdio.h>
#include <signal.h>


#include "snake.c"
#include "board.c"

int main() {
    int count_food = 0;
    init_board();

    //TESTS//
    /*int coords1[][2] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}};
    int coords2[][2] = {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}};
    int length_coords1 = sizeof coords1 / sizeof coords1[0];
    int length_coords2 = sizeof coords2 / sizeof coords2[0];

    struct Snake snake1 = create_snake(length_coords1, coords1);
    struct Snake snake2 = create_snake(length_coords2, coords2);
    add_snake_to_board(snake1.head);
    add_snake_to_board(snake2.head);

    place_random_food(&count_food);

    for (int i = 0; i < 2; i++) {
        move(&snake1, &snake1.head, snake1.direction_x, snake1.direction_y, &count_food);
    }

    set_direction(&snake2, DIRECTION_UP);

    for (int i = 0; i < 2; i++) {
        move(&snake2, &snake2.head, snake2.direction_x, snake2.direction_y, &count_food);
    }

    print_board();*/


    //CODE//
    // Snake starts in the middle and is 3 squares big
    int init_coordinates[][2] = {{(BOARD_WIDTH/2)+2, (BOARD_HEIGHT/2)+2}, {(BOARD_WIDTH/2)+1, (BOARD_HEIGHT/2)+1}, {BOARD_WIDTH/2, BOARD_HEIGHT/2}}; 
    struct Snake snake = create_snake(3, init_coordinates);
    add_snake_to_board(snake.head);

    place_random_food(&count_food);

    int pid = fork(); //Make a process to move snake every second
    if (pid == 0){
        while(snake.isAlive)
        {
            sleep(1);
            move(&snake, &snake.head, snake.direction_x, snake.direction_y, &count_food);
        }
        exit(0);
    }
    
    while (snake.isAlive){
        int keypress = getchar();
        fflush(stdin);

        //Move with wasd for debugging purposes, replace with button input when they are implemented
        switch(keypress){
            case 'w':
                set_direction(&snake, DIRECTION_UP);
                break;
            case 's':
                set_direction(&snake, DIRECTION_DOWN);
                break;
            case 'd':
                set_direction(&snake, DIRECTION_RIGHT);
                break;
            case 'a':
                set_direction(&snake, DIRECTION_LEFT);
                break;
        }
        //TODO: randomly drop food if no food is present
    }

    int waitstatus;
    waitpid(pid,&waitstatus, 0); //Only one child, so need only wait for one child process to finish
    return(0);
}