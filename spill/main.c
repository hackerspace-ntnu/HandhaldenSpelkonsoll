#include "snake.h"
#include "board.h"
#include "constants.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h> 

#include "snake.c"
#include "board.c"
#include "multiplayer_functions.c"

int main() {
    int game_on = 1;
    int count_food = 0;
    int do_movement = 1;
    char keypress[3];

    struct multiplayer_info **multi_info_buffer;
    multi_info_buffer = malloc(sizeof(struct multiplayer_info)*MULTIPLAYER_BUFFER_SIZE);
    int *multi_info_buffer_stack_pointer = malloc(sizeof(int));
    *multi_info_buffer_stack_pointer = 0;

    int snake_id_counter = 0;
    init_board();
   
    struct Snake snake1;
    struct Snake snake2;
    struct Snake snake3;
    struct Snake snake4;
 
    int init_coordinates1[][2] = {{0, 0}, {1, 0}, {2, 0}}; 
    int init_coordinates2[][2] = {{BOARD_WIDTH-0, BOARD_HEIGHT-1}, {BOARD_WIDTH-2, BOARD_HEIGHT-1}, {BOARD_WIDTH-3, BOARD_HEIGHT-1}}; 
    int init_coordinates3[][2] = {{0, BOARD_HEIGHT-1}, {1, BOARD_HEIGHT-1}, {2, BOARD_HEIGHT-1}}; 
    int init_coordinates4[][2] = {{BOARD_WIDTH-1, 0}, {BOARD_WIDTH-2, 0}, {BOARD_WIDTH-3, 0}}; 
    
    //CODE//
    // 1 player: snake1 starts in the middle and is 3 squares big
    // 1 < player: snake1 starts in the upper left corner and is 3 squares big
    switch (PLAYER_NUMBER){
    case 1:
        // Middle of the board (There must be a better way to implement this, but I'm sleepy)
        init_coordinates1[0][0] = (BOARD_WIDTH/2); 
        init_coordinates1[1][0] = (BOARD_WIDTH/2)+1; 
        init_coordinates1[2][0] = (BOARD_WIDTH/2)+2; 
        init_coordinates1[0][1] = BOARD_HEIGHT/2; 
        init_coordinates1[1][1] = BOARD_HEIGHT/2; 
        init_coordinates1[2][1] = BOARD_HEIGHT/2; 

        snake1 = create_snake(3, init_coordinates1, &snake_id_counter);
        add_snake_to_board(snake1.head);

        //initial food
        place_random_food(&count_food); 
        break;

    case 2:
        snake1 = create_snake(3, init_coordinates1, &snake_id_counter);
        snake2 = create_snake(3, init_coordinates2, &snake_id_counter);
        add_snake_to_board(snake1.head);
        add_snake_to_board(snake2.head);

        //initial food
        place_random_food(&count_food);
        break;
    
    case 3:
        snake1 = create_snake(3, init_coordinates1, &snake_id_counter);
        snake2 = create_snake(3, init_coordinates2, &snake_id_counter);
        snake3 = create_snake(3, init_coordinates3, &snake_id_counter);
        add_snake_to_board(snake1.head);
        add_snake_to_board(snake2.head);
        add_snake_to_board(snake3.head);

        //initial food
        place_random_food(&count_food);
        place_random_food(&count_food);
        break;
    
    case 4:
        snake1 = create_snake(3, init_coordinates1, &snake_id_counter);
        snake2 = create_snake(3, init_coordinates2, &snake_id_counter);
        snake3 = create_snake(3, init_coordinates3, &snake_id_counter);
        snake4 = create_snake(3, init_coordinates4, &snake_id_counter);
       
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
   
   printf("Game start! Press w, s, a or d to move\n");
    while (snake1.isAlive){
        fflush(stdin);
        fgets(keypress, 2, stdin);
        keypress[strcspn(keypress, "\r\n")] = 0;
        /* int keypress = getchar();
        fflush(stdin); */

        printf("input: %s\n", keypress);
        //Move with wasd for debugging purposes, replace with button input when they are implemented
        if (!strcmp(keypress, "w")){
            printf("w\n");
            set_direction(&snake1, DIRECTION_UP);
        }
        else if (!strcmp(keypress, "s")){
            printf("s\n");
            set_direction(&snake1, DIRECTION_DOWN);
        }
        else if (!strcmp(keypress, "d")){
            printf("d\n");
            set_direction(&snake1, DIRECTION_RIGHT);
        }
        else if (!strcmp(keypress, "a")){
            printf("a\n");
            set_direction(&snake1, DIRECTION_LEFT);
        }
        /* switch(keypress){
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
        } */

        if(*multi_info_buffer_stack_pointer > 0){ // If there are updates from other players in the buffer
            struct multiplayer_info *m_info = multi_info_buffer[*multi_info_buffer_stack_pointer];
            switch (m_info->id)
            {
            case 0:
                set_direction(&snake1, m_info->direction);
                //Send ACK? Nah..
                break;
            
            case 1:
                if(PLAYER_NUMBER <= 2){
                    set_direction(&snake2, m_info->direction);
                    //Send ACK? Nah..
                }
                break;

            case 2:
                if(PLAYER_NUMBER <= 3){
                    set_direction(&snake3, m_info->direction);
                    //Send ACK? Nah..
                }
                break;

            case 3:
                if(PLAYER_NUMBER <= 4){
                    set_direction(&snake4, m_info->direction);
                    //Send ACK?
                }
                break;
            
            default:
                break;
            }

            if(m_info->new_food & IS_HOST){ //restricted food, only master snake can give it out
                place_food_at_coords(m_info->food_coord_x, m_info->food_coord_y, &count_food);
            }
        }

        //Just to test multiple snake movement
        set_direction(&snake2, (rand() % 4));
        set_direction(&snake3, (rand() % 4));
        set_direction(&snake4, (rand() % 4));

        if(do_movement){ //Should be set to 1 every second
            move(&snake1, &snake1.head, snake1.direction_x, snake1.direction_y, &count_food);
            move(&snake2, &snake2.head, snake2.direction_x, snake2.direction_y, &count_food);
            move(&snake3, &snake3.head, snake3.direction_x, snake3.direction_y, &count_food);
            move(&snake4, &snake4.head, snake4.direction_x, snake4.direction_y, &count_food);
            print_board();
            //do_movement = 0;
            
        }
    }
    printf("Game over\n");
    free(multi_info_buffer);
    return(0);
}