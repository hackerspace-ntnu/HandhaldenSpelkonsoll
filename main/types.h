#ifndef TYPES_H
#define TYPES_H

// Forward declaration
struct snake_t;

typedef struct body_t {
    short int x;
    short int y;
    bool isHead; // (1=true, 0=false)
    struct body_t* next; // Pointer to next part of Body
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

#endif
