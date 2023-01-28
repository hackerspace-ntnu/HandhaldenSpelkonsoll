#include <stdbool.h>

#ifndef SNAKE_H
#define SNAKE_H

struct snake_t;

typedef struct body_t {
    short int x;
    short int y;
    bool isHead; // (1=true, 0=false)
    struct  body_t* next; // Pointer to next part of Body
    struct body_t* prev; // Pointer to previous part of Body
    struct snake_t* snake;
} body_t;

typedef struct board_piece_t {
    short int piece_type;
    body_t* part;
} board_piece_t;

typedef struct snake_t {
    short int id;
    short int direction_x;
    short int direction_y;
    body_t* head;
    bool isAlive;
    //Add colour for easier multiplayer?
} snake_t;

struct multiplayer_info{
    short int id; // To know which snake to update
    int direction; // UP, DOWN, LEFT OR RIGHT
    int new_food; // 0 = no new food, 1 = new food (check for its coordinates)
    int food_coord_x; // When new food is placed, use this to signal where
    int food_coord_y;// When new food is placed, use this to signal where
};

typedef struct move_all{
    struct multiplayer_info player0;
    struct multiplayer_info player1;
    struct multiplayer_info player2;
    struct multiplayer_info player3;
}move_all;


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