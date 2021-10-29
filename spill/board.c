
#define SCREEN_HEIGHT 160
#define SCREEN_WIDTH 240

#define BOARD_HEIGHT 16
#define BOARD_WIDTH 24

#define BLOCK_BLANK 0
#define BLOCK_FOOD 1

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
    board[y][x] = BLOCK_FOOD;
}
