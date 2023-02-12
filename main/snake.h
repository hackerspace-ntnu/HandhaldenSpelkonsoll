#include <stdbool.h>
#include "types.h"

#ifndef SNAKE_H
#define SNAKE_H

void push(board_piece_t* board, body_t** head_ref, snake_t* snake, short int new_x, short int new_y);
void insertAfter(board_piece_t* board, body_t* prev_node, short int new_x, short int new_y);
void append(board_piece_t* board, body_t** head_ref, short int new_x, short int new_y);
body_t* get_head(body_t* bodypart);
body_t* get_tail(body_t* bodypart);
void move(board_piece_t* board, snake_t* snake, body_t** node, short int direction_x, short int direction_y, int* count_food);
void set_direction(snake_t* snake, int direction);
void split_snake(board_piece_t* board, snake_t* snake, body_t** node, int* count_food);
snake_t create_snake(board_piece_t* board, int length, int coords[][2], int* snake_id_counter);
int get_snake_length(body_t* head);

#endif
