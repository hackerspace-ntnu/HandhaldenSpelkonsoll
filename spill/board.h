void init_board(void);
int get_square_value(int x, int y);
void set_square_value(int x, int y, int value);
void add_snake_to_board(struct Body *snake_head);
void place_random_food(void);
char convert_board_int(int num);
void print_board();