/* #include "snake.h"
#include "board.h"
#include "constants.h" */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

struct BoardPiece board[BOARD_HEIGHT][BOARD_WIDTH];
int count_food;

void init_board(void) {
	// Initialize the board with only 0s (clear blocks)
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
            set_square_value(j, i, BLOCK_BLANK, NULL);
		}
	}
}

struct BoardPiece get_square_value(int x, int y) {
    if (x >= BOARD_WIDTH) x = BOARD_WIDTH - 1;
    else if (x < 0) x = 0;
    
    if (y >= BOARD_HEIGHT) y = BOARD_HEIGHT - 1;
    else if (y < 0) y = 0;

    return board[y][x];
}

void set_square_value(int x, int y, short int piece_type, struct Body* part) {
    if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT) {
        return;
    }
    
    struct BoardPiece piece = board[y][x];
    piece.piece_type = piece_type;
    piece.part = part;
    board[y][x] = piece;
}

// To be used under initialization, put a whole snake on the board
void add_snake_to_board(struct Body* snake_head){
    struct Body* snake_part = snake_head;
    do {
        set_square_value(snake_part->x, snake_part->y, BLOCK_SNAKE, snake_part);
        snake_part = snake_part->next;
    } while (snake_part->next != NULL);
    set_square_value(snake_part->x, snake_part->y, BLOCK_SNAKE, snake_part);
}

// Creates and prints printable board out of current board
void print_board(){
    char string_board[BOARD_HEIGHT * BOARD_WIDTH + BOARD_HEIGHT];
    char *current_char = &string_board[0];
    char board_value;
    for (int i = 0; i<BOARD_HEIGHT; i++){
        for (int j= 0; j<BOARD_WIDTH; j++){
            board_value = convert_board_int(board[i][j]); // Translates int on the board to a defined char
            *current_char = board_value; // Adds the character to the printed board
            current_char++;
        }
        *current_char = '\n'; // Seperates the rows
        current_char++;
    }
    printf("%s", string_board); // Prints the board
}

// Translates an int on the digital board to a char for visualization when printing
char convert_board_int(struct BoardPiece piece){
    if (piece.piece_type == BLOCK_BLANK) {
        return '#';
    } else if (piece.piece_type == BLOCK_FOOD) {
        return 'f';
    } else {
        return 's';
    }
}

void place_random_food(int* count_food) {
    int x;
    int y;
    int existing_value;

    do {
        // Pick new coordinates for where the food should be placed
        x = 1 + (rand() % (BOARD_WIDTH - 1));
        y = 1 + (rand() % (BOARD_HEIGHT - 1));
        // Get the value already present at the new coordinates
        existing_value = get_square_value(x, y).piece_type;
        // Pick new coordinates as long as the new coordinates already contains a block
    } while (existing_value != BLOCK_BLANK);

    // Update the board with the new block
    place_food_at_coords(x, y, count_food);
}

void place_food_at_coords(int x, int y, int* count_food) {
    set_square_value(x, y, BLOCK_FOOD, NULL);
    (*count_food)++;
}
