#include "constants.h"
#include "board.h"
#include "snake.h"
// Arduino libraries
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI(SCREEN_WIDTH, SCREEN_HEIGHT); 

int count_food = 0;
int do_movement = 0;

struct multiplayer_info **multi_info_buffer = NULL;

int *multi_info_buffer_stack_pointer = (int*)malloc(sizeof(int));
int snake_id_counter = 0;


struct Snake snake1;
struct Snake snake2;
struct Snake snake3;
struct Snake snake4;

int init_coordinates1[][2] = {{0, 0}, {1, 0}, {2, 0}}; 
int init_coordinates2[][2] = {{BOARD_WIDTH-0, BOARD_HEIGHT-1}, {BOARD_WIDTH-2, BOARD_HEIGHT-1}, {BOARD_WIDTH-3, BOARD_HEIGHT-1}}; 
int init_coordinates3[][2] = {{0, BOARD_HEIGHT-1}, {1, BOARD_HEIGHT-1}, {2, BOARD_HEIGHT-1}}; 
int init_coordinates4[][2] = {{BOARD_WIDTH-1, 0}, {BOARD_WIDTH-2, 0}, {BOARD_WIDTH-3, 0}}; 

void serial_print_board();


void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(3); // when the pins are on the left side, the top left corner is now (0,0)
  tft.fillScreen(TFT_BLACK);
  // drawFrame();
  // drawGrid();
  tft.fillRect(0, 0, SCREEN_HEIGHT/BOARD_HEIGHT, SCREEN_HEIGHT/BOARD_HEIGHT, TFT_WHITE); 
  multi_info_buffer = (struct multiplayer_info**)malloc(sizeof(struct multiplayer_info)*MULTIPLAYER_BUFFER_SIZE);
  *multi_info_buffer_stack_pointer = 0;
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
    
    case 3:
        snake1 = create_snake(3, init_coordinates1, &snake_id_counter);
        snake2 = create_snake(3, init_coordinates2, &snake_id_counter);
        snake3 = create_snake(3, init_coordinates3, &snake_id_counter);
        add_snake_to_board(snake1.head);
        add_snake_to_board(snake2.head);
        add_snake_to_board(snake3.head);

        //initial food
        place_random_food(&count_food);
        place_random_food(&count_food);
        break;
    
    case 4:
        snake1 = create_snake(3, init_coordinates1, &snake_id_counter);
        snake2 = create_snake(3, init_coordinates2, &snake_id_counter);
        snake3 = create_snake(3, init_coordinates3, &snake_id_counter);
        snake4 = create_snake(3, init_coordinates4, &snake_id_counter);
       
        add_snake_to_board(snake1.head);
        add_snake_to_board(snake2.head);
        add_snake_to_board(snake3.head);
        add_snake_to_board(snake4.head);
       
        //initial food
        place_random_food(&count_food);
        place_random_food(&count_food);
        break;

    default:
         //Error, no more players than 4, and no negative players
        break;
    }



}

void loop() {
  if (snake1.isAlive){

       /*  if(*multi_info_buffer_stack_pointer > 0){ // If there are updates from other players in the buffer
            struct multiplayer_info *m_info = multi_info_buffer[*multi_info_buffer_stack_pointer];
            switch (m_info->id)
            {
            case 0:
                set_direction(&snake1, m_info->direction);
                //Send ACK? Nah..
                break;
            
            case 1:
                if(PLAYER_NUMBER <= 2){
                    set_direction(&snake2, m_info->direction);
                    //Send ACK? Nah..
                }
                break;

            case 2:
                if(PLAYER_NUMBER <= 3){
                    set_direction(&snake3, m_info->direction);
                    //Send ACK? Nah..
                }
                break;

            case 3:
                if(PLAYER_NUMBER <= 4){
                    set_direction(&snake4, m_info->direction);
                    //Send ACK?
                }
                break;
            
            default:
                break;
            }

            if(m_info->new_food & IS_HOST){ //restricted food, only master snake can give it out
                place_food_at_coords(m_info->food_coord_x, m_info->food_coord_y, &count_food);
            }
        } */

        //Just to test multiple snake movement
        set_direction(&snake2, (rand() % 4));
        Serial.printf("Snake2 x: %d, y: %d\n", snake2.direction_x, snake2.direction_y);
        set_direction(&snake3, (rand() % 4));
        Serial.printf("Snake3 x: %d, y: %d\n", snake3.direction_x, snake3.direction_y);
        set_direction(&snake4, (rand() % 4));
        Serial.printf("Snake4 x: %d, y: %d\n", snake4.direction_x, snake4.direction_y);


        if(do_movement){ //Should be set to 1 every second
            move(&snake1, &snake1.head, snake1.direction_x, snake1.direction_y, &count_food);
            move(&snake2, &snake2.head, snake2.direction_x, snake2.direction_y, &count_food);
            move(&snake3, &snake3.head, snake3.direction_x, snake3.direction_y, &count_food);
            move(&snake4, &snake4.head, snake4.direction_x, snake4.direction_y, &count_food);
            serial_print_board();
            //do_movement = 0;
            
        }
        snake1.isAlive = false;
    }
}



// void drawFrame() {
//   tft.drawFastVLine(0, 0, w, TFT_GREEN);
//   tft.drawFastVLine(h-1, 0, w, TFT_GREEN);
//   tft.drawFastHLine(0, 0, h, TFT_GREEN);
//   tft.drawFastHLine(0, w-1, h, TFT_GREEN);
// }

// void drawGrid() {
//   for (int i=BLOCK_SIZE; i<h; i+=BLOCK_SIZE) {
//     tft.drawFastVLine(i, 0, w, TFT_GREEN);
//   }
//   for (int j=BLOCK_SIZE; j<w; j+=BLOCK_SIZE) {
//     tft.drawFastHLine(0, j, h, TFT_GREEN);
//   }
// }

// void moveBlock() {
//   //   tft.drawRect(oldX, oldY, BLOCK_SIZE, BLOCK_SIZE, TFT_GREEN);
//   // tft.fillRect(oldX, oldY, BLOCK_SIZE, BLOCK_SIZE, TFT_BLACK);
//   // tft.fillRect(xPos, yPos, BLOCK_SIZE, BLOCK_SIZE, TFT_WHITE); 
//   delay(100);
  
// }

void serial_print_board(){
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
    Serial.printf("%s", string_board); // Prints the board
}