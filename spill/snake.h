struct Body {
    short int x;
    short int y;
    char isHead; // (1=true, 0=false)
    struct Body* next; // Pointer to next part of Body
    struct Body* prev; // Pointer to previous part of Body
};

void push(struct Body** head_ref, short int new_x, short int new_y);
void insertAfter(struct Body* prev_node, short int new_x, short int new_y);
void append(struct Body** head_ref, short int new_x, short int new_y);
struct Body* get_head(struct Body* bodypart);
struct Body* get_tail(struct Body* bodypart);
void move(struct Body** node, short int direction_x, short int direction_y, bool eat);
void printList(struct Body* node);
struct Body* initialize_snake(void);