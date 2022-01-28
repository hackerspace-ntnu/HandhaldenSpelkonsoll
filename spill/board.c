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

#include "snake.h"
#include "board.h"
#include "constants.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int board[BOARD_HEIGHT][BOARD_WIDTH];
int count_food;

void init_board(void) {
	// Initialize the board with only 0s (clear blocks)
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			board[i][j] = 0;
		}
	}
}

int get_square_value(int x, int y) {
    return board[y][x];
}

void set_square_value(int x, int y, int value) {
    board[y][x] = value;
}

// To be used under initialization, put a whole snake on the board
void add_snake_to_board(struct Body *snake_head){
    struct Body *snake_part = snake_head;
    do {
        set_square_value(snake_part->x, snake_part->y, BLOCK_SNAKE);
        snake_part = snake_part->next;
    } while (snake_part->next != NULL);
}

//Creates and prints printable board out of current board
void print_board(){
    char string_board[BOARD_HEIGHT*BOARD_WIDTH+BOARD_HEIGHT];
    char *current_char=&string_board[0];
    char board_value;
    for (int i = 0; i<BOARD_HEIGHT; i++){
        for (int j= 0; j<BOARD_WIDTH; j++){
            board_value = convert_board_int(board[i][j]); //Transelates int on the board to a defined char
            *current_char = board_value; //Adds the character to the printed board
            current_char++;
        }
        *current_char = '\n'; // Seperates the rows
        current_char++;
    }
    printf("%s", string_board); //Prints the board
}

//Transelates an int on the digital board to a char for visualization when printing
char convert_board_int(int num){
    switch (num) 
    {
    case 0:
        return '#';
        break;
    case 1:
        return 'f';
        break;
    case 2:
        return 's';
        break;
    default:
        return ' ';
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
        existing_value = get_square_value(x, y);
        // Pick new coordinates as long as the new coordinates already contains a block
    } while (existing_value != BLOCK_BLANK);

    // Update the board with the new block
    place_food_at_coords(x, y, count_food);
}

void place_food_at_coords(int x, int y, int* count_food) {
    set_square_value(x, y, BLOCK_FOOD);
    (*count_food)++;
}

/*int main(int argc, char const *argv[])
{
    init_board();
    printf("Board init clear\n");
    set_square_value(2,2,1);
    set_square_value(2,3,2);
    printf("Square set cleared\n");
    print_board();
    return 0;
}*/
