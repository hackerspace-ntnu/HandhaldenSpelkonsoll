#include "board.h"
#include "snake.h"
#include "button.h"
#include "lvgl.h"
#include "lvgl_helpers.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "esp_timer.h"
#include "esp_heap_caps.h"

#define LV_TICK_PERIOD_MS 1

board_piece_t* p_board;
snake_t test_snake;
int tick = 0;

lv_obj_t* brd_lv_obj_t[BOARD_HEIGHT*BOARD_WIDTH];
lv_obj_t* bkgrnd;
lv_obj_t* block;

static board_piece_t board[BOARD_HEIGHT * BOARD_WIDTH];
board_piece_t* p_board = &board[0];

static void lv_tick_task(void *arg);
static void guiTask(void *pvParameter);
void draw_board(board_piece_t* p);

void app_main(void){

    int tick = 0;
    int count_food = 0;
    int do_movement = 1;
    int snake_id_counter = 0;

    snake_t snake1;
    snake_t snake2;

    int init_coordinates1[][2] = {{0, 0}, {1, 0}, {2, 0}}; 
    int init_coordinates2[][2] = {{BOARD_WIDTH-0, BOARD_HEIGHT-1}, {BOARD_WIDTH-2, BOARD_HEIGHT-1}, {BOARD_WIDTH-3, BOARD_HEIGHT-1}}; 
    init_board(p_board);

    switch (PLAYER_NUMBER){
        case 1:
            // Middle of the board
            init_coordinates1[0][0] = (BOARD_WIDTH/2); 
            init_coordinates1[1][0] = (BOARD_WIDTH/2)+1; 
            init_coordinates1[2][0] = (BOARD_WIDTH/2)+2; 
            init_coordinates1[0][1] = BOARD_HEIGHT/2; 
            init_coordinates1[1][1] = BOARD_HEIGHT/2; 
            init_coordinates1[2][1] = BOARD_HEIGHT/2; 

            test_snake = create_snake(p_board, 3, init_coordinates1, &snake_id_counter);
            add_snake_to_board(p_board, test_snake.head);

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
    
    xTaskCreatePinnedToCore(guiTask, "gui", 4096*2, NULL, 0, NULL, 1);

    
    while (test_snake.isAlive) {
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

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

    bkgrnd = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_width(bkgrnd, SCREEN_WIDTH);
    lv_obj_set_height(bkgrnd, SCREEN_HEIGHT);
    lv_obj_set_style_local_bg_color(bkgrnd, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_GREEN);

    
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board_piece_t temp = get_square_value(p_board, j, i);
            if (temp.piece_type == BLOCK_SNAKE) {
                brd_lv_obj_t[i*j] = lv_obj_create(bkgrnd, NULL);
                lv_obj_set_height(brd_lv_obj_t[i*j], BLOCK_SIZE);
                lv_obj_set_width(brd_lv_obj_t[i*j], BLOCK_SIZE);
                lv_obj_set_style_local_bg_color(brd_lv_obj_t[i*j], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLUE);
                lv_obj_set_x(brd_lv_obj_t[i*j], j*BLOCK_SIZE);
                lv_obj_set_y(brd_lv_obj_t[i*j], i*BLOCK_SIZE);
            }
            else if (temp.piece_type == BLOCK_FOOD) {
                brd_lv_obj_t[i*j] = lv_obj_create(bkgrnd, NULL);
                lv_obj_set_height(brd_lv_obj_t[i*j], BLOCK_SIZE);
                lv_obj_set_width(brd_lv_obj_t[i*j], BLOCK_SIZE);
                lv_obj_set_style_local_bg_color(brd_lv_obj_t[i*j], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);
                lv_obj_set_x(brd_lv_obj_t[i*j], j*BLOCK_SIZE);
                lv_obj_set_y(brd_lv_obj_t[i*j], i*BLOCK_SIZE);
            }
        }
    }

    
    
    
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
