#include "board.h"
#include "snake.h"
#include "constants.h"
#include "button.h"

#include "lvgl.h"

// void get_multiplayer_struct(struct multiplayer_info *multi_info, struct multiplayer_info **multi_info_buffer, int *stack_pointer){
//     if(multi_info->id > 3){ // Our snakes have ids in the 0-4 range
//         printf("Unknown snake id: %d", multi_info->id);
//     }
//     if (*stack_pointer < MULTIPLAYER_BUFFER_SIZE){
//         multi_info_buffer[*stack_pointer] = multi_info;
//         *stack_pointer++;
//     }    
//     else{
//         printf("No more space on stack, struct dropped\n");
//     }
// }

// void draw_board();
// void gfx_init();

void app_main(void) {

    // lv_obj_set_style_local_bg_color(lv_scr_act(), lv_color_hex(0x003a57), LV_LED_PART_MAIN);

    // /*Create a white label, set its text and align it to the center*/
    // lv_obj_t* label = lv_label_create(lv_scr_act());
    // lv_label_set_text(label, "Hello world");
    // lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0xffffff), LV_LED_PART_MAIN);
    // lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t* bkgrnd = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_set_width(bkgrnd, 135);
	lv_obj_set_height(bkgrnd, 22);
	lv_obj_t* label = lv_label_create(bkgrnd, NULL);
	lv_label_set_text(label, "This is a test");
	lv_obj_set_style_local_text_color(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_obj_set_style_local_bg_color(bkgrnd, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);

	lv_obj_align(bkgrnd, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);
	lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

        
    //     int tick = 0;
    //     int count_food = 0;
    //     int do_movement = 1;

    //     // struct multiplayer_info **multi_info_buffer = NULL;

    //     // int *multi_info_buffer_stack_pointer = (int*)malloc(sizeof(int));
    //     int snake_id_counter = 0;

    //     struct Snake snake1;
    //     struct Snake snake2;

    //     int init_coordinates1[][2] = {{0, 0}, {1, 0}, {2, 0}}; 
    //     int init_coordinates2[][2] = {{BOARD_WIDTH-0, BOARD_HEIGHT-1}, {BOARD_WIDTH-2, BOARD_HEIGHT-1}, {BOARD_WIDTH-3, BOARD_HEIGHT-1}}; 
    // //   gfx_init();
    // // multi_info_buffer = (struct multiplayer_info**)malloc(sizeof(struct multiplayer_info)*MULTIPLAYER_BUFFER_SIZE);
    // // *multi_info_buffer_stack_pointer = 0;
    // init_board();

    // switch (PLAYER_NUMBER){
    //     case 1:
    //         // Middle of the board (There must be a better way to implement this, but I'm sleepy)
    //         init_coordinates1[0][0] = (BOARD_WIDTH/2); 
    //         init_coordinates1[1][0] = (BOARD_WIDTH/2)+1; 
    //         init_coordinates1[2][0] = (BOARD_WIDTH/2)+2; 
    //         init_coordinates1[0][1] = BOARD_HEIGHT/2; 
    //         init_coordinates1[1][1] = BOARD_HEIGHT/2; 
    //         init_coordinates1[2][1] = BOARD_HEIGHT/2; 

    //         snake1 = create_snake(3, init_coordinates1, &snake_id_counter);
    //         add_snake_to_board(snake1.head);

    //         //initial food
    //         place_random_food(&count_food); 
    //         break;

    //     case 2:
    //         snake1 = create_snake(3, init_coordinates1, &snake_id_counter);
    //         snake2 = create_snake(3, init_coordinates2, &snake_id_counter);
    //         add_snake_to_board(snake1.head);
    //         add_snake_to_board(snake2.head);

    //         //initial food
    //         place_random_food(&count_food);
    //         break;
        
    //     default:
    //         break;
    //     }
    //     while (snake1.isAlive) {

    //         //Just to test multiple snake movement
    //         set_direction(&snake2, (rand() % 4));
    //         printf("Snake1 x: %d, y: %d\n", snake1.direction_x, snake1.direction_y);
    //         printf("Snake2 x: %d, y: %d\n", snake2.direction_x, snake2.direction_y);  

    //         if(do_movement){ //Should be set to 1 every second
    //             move(&snake1, &snake1.head, snake1.direction_x, snake1.direction_y, &count_food);
    //             move(&snake2, &snake2.head, snake2.direction_x, snake2.direction_y, &count_food);
    //         }
    //         print_board();  
    //         tick++;          
    //     }
    //     if (tick > 20){
    //     snake1.isAlive = false;
    //     snake2.isAlive = false;
    //     }


}



// void draw_board() {
//      for (int i = 0; i<BOARD_HEIGHT; i++) {
//         for (int j = 0; j<BOARD_WIDTH; j++) {
//             struct BoardPiece temp = board[i][j];
//             if (temp.piece_type == BLOCK_SNAKE) {
//                 tft.fillRect(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, TFT_RED);
//             } else if (temp.piece_type == BLOCK_FOOD) {
//                 tft.fillRect(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, TFT_GREEN);
//             } else {
//               tft.fillRect(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, TFT_BLACK);
//             }
//         }
//     }
// }

// void gfx_init() {
//   tft.init();
//   tft.setRotation(3); // when the pins are on the left side, the top left corner is now (0,0)
//   tft.fillScreen(TFT_BLACK); // black background
// }