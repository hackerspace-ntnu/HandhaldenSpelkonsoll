#include "board.h"
#include "snake.h"
#include <TFT_eSPI.h>

TFT_eSPI tft;

int tick = 0;
int count_food = 0;
int do_movement = 1;

// struct multiplayer_info **multi_info_buffer = NULL;

// int *multi_info_buffer_stack_pointer = (int*)malloc(sizeof(int));
int snake_id_counter = 0;

struct Snake snake1;
struct Snake snake2;

int init_coordinates1[][2] = {{0, 0}, {1, 0}, {2, 0}}; 
int init_coordinates2[][2] = {{BOARD_WIDTH-0, BOARD_HEIGHT-1}, {BOARD_WIDTH-2, BOARD_HEIGHT-1}, {BOARD_WIDTH-3, BOARD_HEIGHT-1}}; 

void serial_print_board();
void draw_board();
void gfx_init();

void setup() {
  Serial.begin(115200);
  gfx_init();
  // multi_info_buffer = (struct multiplayer_info**)malloc(sizeof(struct multiplayer_info)*MULTIPLAYER_BUFFER_SIZE);
  // *multi_info_buffer_stack_pointer = 0;
  init_board();

  switch (PLAYER_NUMBER){
    case 1:
        // Middle of the board (There must be a better way to implement this, but I'm sleepy)
        init_coordinates1[0][0] = (BOARD_WIDTH/2); 
        init_coordinates1[1][0] = (BOARD_WIDTH/2)+1; 
        init_coordinates1[2][0] = (BOARD_WIDTH/2)+2; 
        init_coordinates1[0][1] = BOARD_HEIGHT/2; 
        init_coordinates1[1][1] = BOARD_HEIGHT/2; 
        init_coordinates1[2][1] = BOARD_HEIGHT/2; 

        snake1 = create_snake(3, init_coordinates1, &snake_id_counter);
        add_snake_to_board(snake1.head);

        //initial food
        place_random_food(&count_food); 
        break;

    case 2:
        snake1 = create_snake(3, init_coordinates1, &snake_id_counter);
        snake2 = create_snake(3, init_coordinates2, &snake_id_counter);
        add_snake_to_board(snake1.head);
        add_snake_to_board(snake2.head);

        //initial food
        place_random_food(&count_food);
        break;
    
    default:
        break;
    }
}

void loop() {
  if (snake1.isAlive) {

        //Just to test multiple snake movement
        set_direction(&snake2, (rand() % 4));
        Serial.printf("Snake1 x: %d, y: %d\n", snake1.direction_x, snake1.direction_y);
        Serial.printf("Snake2 x: %d, y: %d\n", snake2.direction_x, snake2.direction_y);  

        if(do_movement){ //Should be set to 1 every second
            move(&snake1, &snake1.head, snake1.direction_x, snake1.direction_y, &count_food);
            move(&snake2, &snake2.head, snake2.direction_x, snake2.direction_y, &count_food);
        }
        draw_board();  
        tick++;          
    }
    if (tick > 20){
      snake1.isAlive = false;
      snake2.isAlive = false;
    }
}

// for debugging purposes
void serial_print_board(){
    char string_board[BOARD_HEIGHT * BOARD_WIDTH + BOARD_HEIGHT];
    char *current_char = &string_board[0];
    char board_value;
    for (int i = 0; i<BOARD_HEIGHT; i++){
        for (int j= 0; j<BOARD_WIDTH; j++){
            board_value = convert_board_int(board[i][j]); 
            *current_char = board_value; 
            current_char++;
        }
        *current_char = '\n';
        current_char++;
    }
    Serial.printf("%s", string_board);
}


void draw_board() {
     for (int i = 0; i<BOARD_HEIGHT; i++) {
        for (int j = 0; j<BOARD_WIDTH; j++) {
            struct BoardPiece temp = board[i][j];
            if (temp.piece_type == BLOCK_SNAKE) {
                tft.fillRect(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, TFT_RED);
            } else if (temp.piece_type == BLOCK_FOOD) {
                tft.fillRect(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, TFT_GREEN);
            } else {
              tft.fillRect(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, TFT_BLACK);
            }
        }
    }
}

void gfx_init() {
  tft.init();
  tft.setRotation(3); // when the pins are on the left side, the top left corner is now (0,0)
  tft.fillScreen(TFT_BLACK); // black background
}