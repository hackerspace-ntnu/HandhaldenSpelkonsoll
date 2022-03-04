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
    int do_movement = 0;
    init_board();
 
    //CODE//
    // Snake starts in the middle and is 3 squares big
    int init_coordinates[][2] = {{(BOARD_WIDTH/2)+2, (BOARD_HEIGHT/2)}, {(BOARD_WIDTH/2)+1, (BOARD_HEIGHT/2)}, {BOARD_WIDTH/2, BOARD_HEIGHT/2}}; 
    struct Snake snake = create_snake(3, init_coordinates);
    add_snake_to_board(snake.head);

    place_random_food(&count_food);

    
    
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
        
        if(count_food < MAX_FOOD_AT_ONCE){
            place_random_food(&count_food);
        }

        

        if(do_movement){ //Should be set to 1 every second
            printf("Inside if\n");
            move(&snake, &snake.head, snake.direction_x, snake.direction_y, &count_food);
            print_board();
            do_movement = 0;
            
        }
    }

    return(0);
}