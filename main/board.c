#include "board.h"

void init_board(board_piece_t* board) {
	// Initialize the board with only 0s (clear blocks)
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
            set_square_value(board, j, i, BLOCK_BLANK, NULL);
		}
	}
}

board_piece_t get_square_value(board_piece_t* board, int x, int y) {
    if (x >= BOARD_WIDTH) x = BOARD_WIDTH - 1;
    else if (x < 0) x = 0;
    
    if (y >= BOARD_HEIGHT) y = BOARD_HEIGHT - 1;
    else if (y < 0) y = 0;

    return board[y * BOARD_WIDTH + x];
}

void set_square_value(board_piece_t* board, int x, int y, short int piece_type, body_t* part) {
    if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT) {
        return;
    }
    
    board_piece_t piece = board[y * BOARD_WIDTH + x];
    piece.piece_type = piece_type;
    piece.part = part;
    board[y * BOARD_WIDTH + x] = piece;
}

// To be used under initialization, put a whole snake on the board
void add_snake_to_board(board_piece_t* board, body_t* snake_head){
    body_t* snake_part = snake_head;
    do {
        set_square_value(board, snake_part->x, snake_part->y, BLOCK_SNAKE, snake_part);
        snake_part = snake_part->next;
    } while (snake_part->next != NULL);
    set_square_value(board, snake_part->x, snake_part->y, BLOCK_SNAKE, snake_part);
}

// Creates and prints printable board out of current board
void print_board(board_piece_t* board){
    char string_board[BOARD_HEIGHT * BOARD_WIDTH + BOARD_HEIGHT];
    char *current_char = &string_board[0];
    char board_value;
    for (int i = 0; i<BOARD_HEIGHT; i++){
        for (int j= 0; j<BOARD_WIDTH; j++){
            board_value = convert_board_int(board[i * BOARD_WIDTH + j]); // Translates int on the board to a defined char
            *current_char = board_value; // Adds the character to the printed board
            current_char++;
        }
        *current_char = '\n'; // Seperates the rows
        current_char++;
    }
    printf("%s", string_board); // Prints the board
}

// Translates an int on the digital board to a char for visualization when printing
char convert_board_int(board_piece_t piece){
    if (piece.piece_type == BLOCK_BLANK) {
        return '#';
    } else if (piece.piece_type == BLOCK_FOOD) {
        return 'f';
    } else {
        return 's';
    }
}

void place_random_food(board_piece_t* board, int* count_food) {
    int x;
    int y;
    int existing_value;

    do {
        // Pick new coordinates for where the food should be placed
        x = 1 + (rand() % (BOARD_WIDTH - 1));
        y = 1 + (rand() % (BOARD_HEIGHT - 1));
        // Get the value already present at the new coordinates
        existing_value = get_square_value(board, x, y).piece_type;
        // Pick new coordinates as long as the new coordinates already contains a block
    } while (existing_value != BLOCK_BLANK);

    // Update the board with the new block
    place_food_at_coords(board, x, y, count_food);
}

void place_food_at_coords(board_piece_t* board, int x, int y, int* count_food) {
    set_square_value(board, x, y, BLOCK_FOOD, NULL);
    (*count_food)++;
}
