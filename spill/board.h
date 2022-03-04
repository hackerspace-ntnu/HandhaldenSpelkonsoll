#include <stdint.h>

struct BoardPiece {
    short int piece_type;
    short int x;
    short int y;

};

void init_board(void);
long int get_square_value(int x, int y);
void set_square_value(int x, int y, long int value);
void add_snake_to_board(struct Body *snake_head);
void place_random_food(int* count_food);
void place_food_at_coords(int x, int y, int* count_food);
char convert_board_int(int num);
void print_board();