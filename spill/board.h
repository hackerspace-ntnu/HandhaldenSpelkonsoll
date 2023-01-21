#include "constants.h"

#ifndef BOARD_H
#define BOARD_H

struct BoardPiece {
    short int piece_type;
    struct Body* part;
};

#ifdef __cplusplus
 extern "C" {
#endif

void init_board(void);
struct BoardPiece get_square_value(int x, int y);
void set_square_value(int x, int y, short int piece_type, struct Body* part);
void add_snake_to_board(struct Body* snake_head);
void place_random_food(int* count_food);
void place_food_at_coords(int x, int y, int* count_food);
char convert_board_int(struct BoardPiece piece);
void print_board();

struct BoardPiece board[BOARD_HEIGHT][BOARD_WIDTH];

#ifdef __cplusplus
 }
#endif

#endif