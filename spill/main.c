#include "snake.h"
#include "board.h"
#include "constants.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include "snake.c"
#include "board.c"

int main() {
    int count_food = 0;
    int do_movement = 1;
    init_board();
    
    struct Snake snake1;
    struct Snake snake2;
    struct Snake snake3;
    struct Snake snake4;

    int init_coordinates1[][2] = {{(BOARD_WIDTH/2)+2, (BOARD_HEIGHT/2)}, {(BOARD_WIDTH/2)+1, (BOARD_HEIGHT/2)}, {BOARD_WIDTH/2, BOARD_HEIGHT/2}}; 
    int init_coordinates2[][2] = {{BOARD_WIDTH-3, BOARD_HEIGHT}, {BOARD_WIDTH-2, BOARD_HEIGHT}, {BOARD_WIDTH-1, BOARD_HEIGHT}}; 
    int init_coordinates3[][2] = {{2, BOARD_HEIGHT}, {1, BOARD_HEIGHT}, {0, BOARD_HEIGHT}}; 
    int init_coordinates4[][2] = {{BOARD_WIDTH-3, 0}, {BOARD_WIDTH-2, 0}, {BOARD_WIDTH-1, 0}}; 

    //CODE//
    // 1 player: snake1 starts in the middle and is 3 squares big
    // 1 < player: snake1 starts in the upper left corner and is 3 squares big
    switch (PLAYER_NUMBER){
    case 1:
        // Middle of the board (There must be a better way to implement this, but I'm sleepy)
        init_coordinates1[0][0] = 2; 
        init_coordinates1[1][0] = 1; 
        init_coordinates1[2][0] = 0; 
        init_coordinates1[0][1] = 0; 
        init_coordinates1[1][1] = 0; 
        init_coordinates1[2][1] = 0; 

        snake1 = create_snake(3, init_coordinates1);
        add_snake_to_board(snake1.head);

        //initial food
        place_random_food(&count_food); 
        break;

    case 2:
        snake1 = create_snake(3, init_coordinates1);
        snake2 = create_snake(3, init_coordinates2);
        add_snake_to_board(snake1.head);
        add_snake_to_board(snake2.head);

        //initial food
        place_random_food(&count_food);
        break;
    
    case 3:
        snake1 = create_snake(3, init_coordinates1);
        snake2 = create_snake(3, init_coordinates2);
        snake3 = create_snake(3, init_coordinates3);
        add_snake_to_board(snake1.head);
        add_snake_to_board(snake2.head);
        add_snake_to_board(snake3.head);

        //initial food
        place_random_food(&count_food);
        place_random_food(&count_food);
        break;
    
    case 4:
        snake1 = create_snake(3, init_coordinates1);
        snake2 = create_snake(3, init_coordinates2);
        snake3 = create_snake(3, init_coordinates3);
        snake3 = create_snake(3, init_coordinates4);
        add_snake_to_board(snake1.head);
        add_snake_to_board(snake2.head);
        add_snake_to_board(snake3.head);
        add_snake_to_board(snake4.head);

        //initial food
        place_random_food(&count_food);
        place_random_food(&count_food);
        break;

    default:
        return 1; //Error, no more players than 4, and no negative players
        break;
    }
    
    while (snake1.isAlive){
        int keypress = getchar();
        fflush(stdin);

        //Move with wasd for debugging purposes, replace with button input when they are implemented
        switch(keypress){
            case 'w':
                set_direction(&snake1, DIRECTION_UP);
                break;
            case 's':
                set_direction(&snake1, DIRECTION_DOWN);
                break;
            case 'd':
                set_direction(&snake1, DIRECTION_RIGHT);
                break;
            case 'a':
                set_direction(&snake1, DIRECTION_LEFT);
                break;
        }

        if(do_movement){ //Should be set to 1 every second
            printf("Inside if\n");
            move(&snake1, &snake1.head, snake1.direction_x, snake1.direction_y, &count_food);
            print_board();
            //do_movement = 0;
            
        }
    }

    return(0);
}