#include "board.h"
#include "snake.h"
#include "constants.h"
#include "button.h"
#include "lvgl.h"

void my_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/
    int32_t x, y;
    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
            // put_px(x, y, *color_p);
            color_p++;
        }
    }

    /* IMPORTANT!!!
     * Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);

}

void my_px_cb(lv_disp_drv_t * disp_drv, uint8_t * buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa)
{
    /* Write to the buffer as required for the display.
     * Write only 1-bit for monochrome displays mapped vertically:*/
 buf += buf_w * (y >> 3) + x;
 if(lv_color_brightness(color) > 128) (*buf) |= (1 << (y % 8));
 else (*buf) &= ~(1 << (y % 8));
}


void app_main(void) {

    lv_init();


    static lv_disp_buf_t disp_buf;
   
       /*Static or global buffer(s). The second buffer is optional*/
    static lv_color_t buf_1[32 * 10];
    static lv_color_t buf_2[32 * 10];

    /*Initialize `disp_buf` with the buffer(s) */
    lv_disp_buf_init(&disp_buf, buf_1, buf_2, 32*10);

    lv_disp_drv_t disp_drv;                 /*A variable to hold the drivers. Can be local variable*/
    lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
    disp_drv.buffer = &disp_buf;            /*Set an initialized buffer*/
    disp_drv.hor_res = 480;
    disp_drv.ver_res = 320;
    // disp_drv.set_px_cb = my_px_cb;
    disp_drv.flush_cb = my_flush_cb;        /*Set a flush callback to draw to the display*/
    lv_disp_t* disp;
    disp = lv_disp_drv_register(&disp_drv); /*Register the driver and save the created display objects*/
    

    lv_obj_t* bkgrnd = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_set_width(bkgrnd, 135);
	lv_obj_set_height(bkgrnd, 22);
	lv_obj_t* label = lv_label_create(bkgrnd, NULL);
	lv_label_set_text(label, "This is a test");
	lv_obj_set_style_local_text_color(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_obj_set_style_local_bg_color(bkgrnd, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);

	// lv_obj_align(bkgrnd, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);
	// lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

    // lv_tick_inc(10);
        
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