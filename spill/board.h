#define SCREEN_HEIGHT 320
#define SCREEN_WIDTH 480

#define BOARD_HEIGHT 32
#define BOARD_WIDTH 48

#define BLOCK_BLANK 0
#define BLOCK_FOOD 1
#define BLOCK_SNAKE 2

void init_board(void);
int get_square_value(int x, int y);
void set_square_value(int x, int y, int value);
void add_snake_to_board(struct Body *snake_head);
void place_random_food(void);
char convert_board_int(int num);