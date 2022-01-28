void init_board(void);
int get_square_value(int x, int y);
void set_square_value(int x, int y, int value);
void add_snake_to_board(struct Body *snake_head);
void place_random_food(int* count_food);
void place_food_at_coords(int x, int y, int* count_food);
char convert_board_int(int num);
void print_board();