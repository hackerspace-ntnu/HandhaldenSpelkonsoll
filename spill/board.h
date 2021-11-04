#define SCREEN_HEIGHT 160
#define SCREEN_WIDTH 240

#define BOARD_HEIGHT 16
#define BOARD_WIDTH 24

#define BLOCK_BLANK 0
#define BLOCK_FOOD 1
#define BLOCK_SNAKE 2

void init_board(void);
int get_square_value(int x, int y);
void set_square_value(int x, int y, int value);
void initialize_snake(struct Body *snake_head);
void place_random_food(void);