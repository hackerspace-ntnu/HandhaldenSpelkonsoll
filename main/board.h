#include "constants.h"
#include "types.h"

#ifndef BOARD_H
#define BOARD_H

void init_board(board_piece_t* board);
board_piece_t get_square_value(board_piece_t* board, int x, int y);
void set_square_value(board_piece_t* board, int x, int y, short int piece_type, body_t* part);
void add_snake_to_board(board_piece_t* board, body_t* snake_head);
void place_random_food(board_piece_t* board, int* count_food);
void place_food_at_coords(board_piece_t* board, int x, int y, int* count_food);
char convert_board_int(board_piece_t piece);
void print_board(board_piece_t* board);

#endif
