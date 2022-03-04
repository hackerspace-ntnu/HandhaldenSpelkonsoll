#include "snake.h"
#include "board.h"
#include "constants.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
//#include <semaphore.h>


#include "snake.c"
#include "board.c"

//sem_t semaphore_move;

int main() {
    int count_food = 0;
    int do_movement = 0;
    init_board();
    //char test[50];
 
    //CODE//
    // Snake starts in the middle and is 3 squares big
    int init_coordinates[][2] = {{(BOARD_WIDTH/2)+2, (BOARD_HEIGHT/2)}, {(BOARD_WIDTH/2)+1, (BOARD_HEIGHT/2)}, {BOARD_WIDTH/2, BOARD_HEIGHT/2}}; 
    struct Snake snake = create_snake(3, init_coordinates);
    add_snake_to_board(snake.head);

    place_random_food(&count_food);

    /* sem_init(&semaphore_move, 0, 1); // Initialize the semaphore
    int semaphore_value;
    int pid = fork(); //Make a process to move snake every second
    if (pid == 0){
        while(snake.isAlive)
        {   
            //print_board();
            // sleep(1);
            //sem_post(&semaphore_move); 
            //sem_getvalue(&semaphore_move,&semaphore_value);
            //printf("Inside thread: %d\n", semaphore_value);
            //move(&snake, &snake.head, snake.direction_x, snake.direction_y, &count_food);
        }
        exit(0);
    } */
    
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

        //printf("sem value: %d\n",sem_getvalue(&semaphore_move,&semaphore_value));

        if(do_movement){ //Should be set to 1 every second, semaphore_value==1
            printf("Inside if\n");
            move(&snake, &snake.head, snake.direction_x, snake.direction_y, &count_food);
            print_board();
            do_movement = 0;
            //sem_wait(&semaphore_move);
        }
    }

    //int waitstatus; //For degbug of status of the child
    //waitpid(pid, &waitstatus, 0); //Only one child, so need only wait for one child process to finish
    //sem_destroy(&semaphore_move); // Free the memory of the semaphore
    return(0);
}