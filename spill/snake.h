#include <stdbool.h>

struct Body {
    short int x;
    short int y;
    bool isHead; // (1=true, 0=false)
    struct Body* next; // Pointer to next part of Body
    struct Body* prev; // Pointer to previous part of Body
    struct Snake* snake;
};

struct Snake {
    short int id;
    short int direction_x;
    short int direction_y;
    struct Body* head;
    bool isAlive;
    //Add colour for easier multiplayer?
};

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

void push(struct Body** head_ref, struct Snake* snake, short int new_x, short int new_y);
void insertAfter(struct Body* prev_node, short int new_x, short int new_y);
void append(struct Body** head_ref, short int new_x, short int new_y);
struct Body* get_head(struct Body* bodypart);
struct Body* get_tail(struct Body* bodypart);
void move(struct Snake* snake, struct Body** node, short int direction_x, short int direction_y, int* count_food);
void set_direction(struct Snake* snake, int direction);
void split_snake(struct Snake* snake, struct Body** node, int* count_food);
struct Snake create_snake(int length, int coords[][2], int* snake_id_counter);
int get_snake_length(struct Body* head);