// #ifdef _WIN_64
//     #include <windows.h>
//     #define KEY_UP 87
//     #define KEY_DOWN 83
//     #define KEY_LEFT 65
//     #define KEY_RIGHT 68

//     bool key_is_pressed(int key) {
//     return (bool)(GetKeyState(key) & 0x8000);
// }

// #else
//     #include <curses.h>
//     initscr();
//     keypad(stdscr, true);
// #endif


#include "board.h"
#define SCREEN_HEIGHT 320
#define SCREEN_WIDTH 480

#define BOARD_HEIGHT 32
#define BOARD_WIDTH 48

#define BLOCK_BLANK 0
#define BLOCK_FOOD 1
#define BLOCK_SNAKE 2

int board[BOARD_HEIGHT][BOARD_WIDTH];

void init_board(void) {
    int i;
	int j;

	// Initialize the board with only 0s (clear blocks)
	for (i = 0; i < BOARD_HEIGHT; i++) {
		for (j = 0; j < BOARD_WIDTH; j++) {
			board[i][j] = 0;
		}
	}
}

int get_square_value(int x, int y) {
    return board[y][x];
}

void set_square_value(int x, int y, int value){
    board[y][x] = value;
}

void initialize_snake(struct Body *snake_head){
    struct Body *snake_part = snake_head;
    do{
        set_square_value(snake_part->x, snake_part->y, BLOCK_SNAKE);
        snake_part = snake_part->next;
    }while(snake_part->next != NULL);
}


void place_random_food(void) {
    int x;
    int y;
    int existing_value;

    do {
        // Pick new coordinates for where the food should be placed
        x = 1 + (rand() % (SCREEN_WIDTH - 1));
        y = 1 + (rand() % (SCREEN_HEIGHT - 1));
        // Get the value already present at the new coordinates
        existing_value = get_square_value(x, y);
        // Pick new coordinates as long as the new coordinates already contains a block
    } while (existing_value != BLOCK_BLANK);

    // Update the board with the new block
    set_square_value(x, y, BLOCK_FOOD);
}
