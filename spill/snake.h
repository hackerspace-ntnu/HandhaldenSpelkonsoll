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
};

void push(struct Body** head_ref, struct Snake* snake, short int new_x, short int new_y);
void insertAfter(struct Body* prev_node, short int new_x, short int new_y);
void append(struct Body** head_ref, short int new_x, short int new_y);
struct Body* get_head(struct Body* bodypart);
struct Body* get_tail(struct Body* bodypart);
void move(struct Snake* snake, struct Body** node, short int direction_x, short int direction_y, int* count_food);
void set_direction(struct Snake* snake, int direction);
void split_snake(struct Snake* snake, struct Body** node, int* count_food);
void printList(struct Body* node);
struct Snake create_snake(int length, int coords[][2]);