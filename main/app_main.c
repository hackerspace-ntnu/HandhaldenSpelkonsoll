#include "board.h"
#include "snake.h"
<<<<<<< HEAD
#include "constants.h"
#include "multiplayer.h"
=======
#include "button.h"
#include "lvgl.h"
#include "lvgl_helpers.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "esp_timer.h"
>>>>>>> 5ba565e3f1ddd97bfd589f2c076e1f3f05823fb2

#define LV_TICK_PERIOD_MS 1

static void lv_tick_task(void *arg);
static void guiTask(void *pvParameter);

void app_main(void){

<<<<<<< HEAD

=======
>>>>>>> 5ba565e3f1ddd97bfd589f2c076e1f3f05823fb2
    int tick = 0;
    int count_food = 0;
    int do_movement = 1;
    int snake_id_counter = 0;

    snake_t snake1;
    snake_t snake2;
    static board_piece_t board[BOARD_HEIGHT * BOARD_WIDTH];
    board_piece_t* p_board = &board[0];
    int init_coordinates1[][2] = {{0, 0}, {1, 0}, {2, 0}}; 
    int init_coordinates2[][2] = {{BOARD_WIDTH-0, BOARD_HEIGHT-1}, {BOARD_WIDTH-2, BOARD_HEIGHT-1}, {BOARD_WIDTH-3, BOARD_HEIGHT-1}}; 
    init_board(p_board);
    xTaskCreatePinnedToCore(guiTask, "gui", 4096*2, NULL, 0, NULL, 1);

    switch (PLAYER_NUMBER){
        case 1:
            // Middle of the board
            init_coordinates1[0][0] = (BOARD_WIDTH/2); 
            init_coordinates1[1][0] = (BOARD_WIDTH/2)+1; 
            init_coordinates1[2][0] = (BOARD_WIDTH/2)+2; 
            init_coordinates1[0][1] = BOARD_HEIGHT/2; 
            init_coordinates1[1][1] = BOARD_HEIGHT/2; 
            init_coordinates1[2][1] = BOARD_HEIGHT/2; 

            snake1 = create_snake(p_board, 3, init_coordinates1, &snake_id_counter);
            add_snake_to_board(p_board, snake1.head);

            //initial food
            place_random_food(p_board, &count_food); 
            break;

        case 2:
            snake1 = create_snake(p_board, 3, init_coordinates1, &snake_id_counter);
            snake2 = create_snake(p_board, 3, init_coordinates2, &snake_id_counter);
            add_snake_to_board(p_board, snake1.head);
            add_snake_to_board(p_board, snake2.head);

            //initial food
            place_random_food(p_board, &count_food);
            break;
        
        default:
            break;
    }
    while (snake1.isAlive) {
<<<<<<< HEAD

        //Just to test multiple snake movement
        // set_direction(&snake2, (rand() % 4));
        printf("Snake1 x: %d, y: %d\n", snake1.direction_x, snake1.direction_y);
        printf("Snake2 x: %d, y: %d\n", snake2.direction_x, snake2.direction_y);  

=======
>>>>>>> 5ba565e3f1ddd97bfd589f2c076e1f3f05823fb2
        if(do_movement){ //Should be set to 1 every second
            move(p_board, &snake1, &snake1.head, snake1.direction_x, snake1.direction_y, &count_food);
            move(p_board, &snake2, &snake2.head, snake2.direction_x, snake2.direction_y, &count_food);
        }
<<<<<<< HEAD
        print_board();  
        tick++;     
        vTaskDelay(1000/portTICK_PERIOD_MS);   
=======
        // print_board(p_board);  
        tick++;         
>>>>>>> 5ba565e3f1ddd97bfd589f2c076e1f3f05823fb2
    }
    if (tick > 20){
        snake1.isAlive = false;
        snake2.isAlive = false;
    }
}
<<<<<<< HEAD
=======

SemaphoreHandle_t xGuiSemaphore;

static void guiTask(void *pvParameter) {

    (void) pvParameter;
    xGuiSemaphore = xSemaphoreCreateMutex();

    lv_init();
    esp_timer_init();

    /* Initialize SPI bus used by the drivers */
    lvgl_driver_init();

    /* Use double buffered when not working with monochrome displays */
    lv_color_t* buf1 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
    lv_color_t* buf2 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf1 != NULL);
    assert(buf2 != NULL);


    static lv_disp_buf_t disp_buf;
    lv_disp_buf_init(&disp_buf, buf1, buf2, DISP_BUF_SIZE); /*Initialize `disp_buf` with the buffer(s) */
    lv_disp_drv_t disp_drv; /*A variable to hold the drivers. Can be local variable*/
    lv_disp_drv_init(&disp_drv); /*Basic initialization*/
    disp_drv.flush_cb = disp_driver_flush; /*Set a flush callback to draw to the display*/
    disp_drv.buffer = &disp_buf; /*Set an initialized buffer*/
    lv_disp_drv_register(&disp_drv); /*Register the driver and save the created display objects*/


    /* Create and start a periodic timer interrupt to call lv_tick_inc */
    // const esp_timer_create_args_t periodic_timer_args = {
    //     .callback = &lv_tick_task,
    //     .name = "periodic_gui"
    // };
    // esp_timer_handle_t periodic_timer;
    // ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    // ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));

    lv_obj_t* bkgrnd = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_width(bkgrnd, 135);
    lv_obj_set_height(bkgrnd, 22);
    lv_obj_t* label = lv_label_create(bkgrnd, NULL);
    lv_label_set_text(label, "Hackerspace");
    lv_obj_set_style_local_text_color(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_set_style_local_bg_color(bkgrnd, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLUE);

    while (1) {
        /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
        vTaskDelay(pdMS_TO_TICKS(10));

        /* Try to take the semaphore, call lvgl related function on success */
        if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY)) {
            lv_task_handler();
            xSemaphoreGive(xGuiSemaphore);
       }
    }

    /* A task should NEVER return */
    free(buf1);
    free(buf2);
    vTaskDelete(NULL);
}

static void lv_tick_task(void *arg) {
    (void) arg;

    lv_tick_inc(LV_TICK_PERIOD_MS);
}
>>>>>>> 5ba565e3f1ddd97bfd589f2c076e1f3f05823fb2
