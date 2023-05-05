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
#include "driver/gpio.h"


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

lv_color_t* buf1;
lv_color_t* buf2;
SemaphoreHandle_t xGuiSemaphore;
int direction=0;

gpio_num_t button_pins[4] = {BTN_DP_UP, BTN_B, BTN_DP_RIGHT,BTN_A};

lv_style_t style_snake;
lv_style_t style_blank;
lv_style_t style_food;

void init_buttons() {
    for(int i=0; i<4; i++){
        gpio_set_direction(button_pins[i], GPIO_MODE_INPUT);
    }
}

int read_button(gpio_num_t pin) {
    return gpio_get_level(pin);
}

void app_main(void){

    int tick = 0;
    int count_food = 0;
    int do_movement = 1;
    int snake_id_counter = 0;
    
    init_buttons();

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
    
    lv_init();
    esp_timer_init();
    /* Initialize SPI bus used by the drivers */
    lvgl_driver_init();
    /* Use double buffered when not working with monochrome displays */
    buf1 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
    buf2 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
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
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "periodic_gui"
    };
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 400));
    
    bkgrnd = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_width(bkgrnd, SCREEN_WIDTH);
    lv_obj_set_height(bkgrnd, SCREEN_HEIGHT);
    lv_obj_set_style_local_bg_color(bkgrnd, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_GREEN);

    lv_style_init(&style_snake);
    lv_style_init(&style_blank);
    lv_style_init(&style_food);
    lv_style_set_bg_color(&style_snake, LV_STATE_DEFAULT, LV_COLOR_BLUE);
    lv_style_set_bg_color(&style_blank, LV_STATE_DEFAULT, LV_COLOR_GREEN);
    lv_style_set_bg_color(&style_food, LV_STATE_DEFAULT, LV_COLOR_RED);

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        printf("\n");
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board_piece_t temp = get_square_value(p_board, j, i);
            // short int temp = p_board[0].piece_type;
            brd_lv_obj_t[i*j] = lv_obj_create(bkgrnd, NULL);
            lv_obj_set_height(brd_lv_obj_t[i*j], BLOCK_SIZE);
            lv_obj_set_width(brd_lv_obj_t[i*j], BLOCK_SIZE);
            lv_obj_set_x(brd_lv_obj_t[i*j], j*BLOCK_SIZE);
            lv_obj_set_y(brd_lv_obj_t[i*j], i*BLOCK_SIZE);

            if (temp.piece_type == BLOCK_SNAKE) {
                lv_obj_add_style(brd_lv_obj_t[i*j]  , LV_BTN_PART_MAIN, &style_snake);
                // lv_obj_set_style_local_bg_color(brd_lv_obj_t[i*j], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLUE);
                printf("s");
            }
            else if (temp.piece_type == BLOCK_FOOD) {
                lv_obj_add_style(brd_lv_obj_t[i*j]  , LV_BTN_PART_MAIN, &style_food);
                printf("f");
            } else if (temp.piece_type == BLOCK_BLANK) {
                lv_obj_add_style(brd_lv_obj_t[i*j]  , LV_BTN_PART_MAIN, &style_blank);
                printf("#");
            }
        }
    }


    while (1) { 
        vTaskDelay(pdMS_TO_TICKS(500));

        printf("\n");

        for(int i=0; i<4; i++){
            printf("%d", read_button(button_pins[i]));
        }

        printf("\n");

        if (read_button(button_pins[0])==1) {
            set_direction(&test_snake, DIRECTION_UP);
        }
        if (read_button(button_pins[1])==1) {
            set_direction(&test_snake, DIRECTION_RIGHT);
        }
        if (read_button(button_pins[2])==1) {
            set_direction(&test_snake, DIRECTION_DOWN);
        }
        if (read_button(button_pins[3])==1) {
            set_direction(&test_snake, DIRECTION_LEFT);
        }

        if(do_movement){ //Should be set to 1 every second
            move(p_board, &test_snake, &test_snake.head, test_snake.direction_x, test_snake.direction_y, &count_food);
            print_board(p_board);  
        }

        for (int i = 0; i < BOARD_HEIGHT; i++) {
            printf("\n");

            for (int j = 0; j < BOARD_WIDTH; j++) {
                board_piece_t temp = get_square_value(p_board, j, i);
                // print_board(&temp);
                // printf("%d",temp.piece_type);
                lv_obj_invalidate(brd_lv_obj_t[i*j]);
                lv_obj_set_x(brd_lv_obj_t[i*j], j*BLOCK_SIZE);
                lv_obj_set_y(brd_lv_obj_t[i*j], i*BLOCK_SIZE);

                if (temp.piece_type == BLOCK_SNAKE) {
                lv_obj_add_style(brd_lv_obj_t[i*j]  , LV_BTN_PART_MAIN, &style_snake);
                    printf("s");
                }
                else if (temp.piece_type == BLOCK_FOOD) {
                lv_obj_add_style(brd_lv_obj_t[i*j]  , LV_BTN_PART_MAIN, &style_food);
                    printf("f");
                } else if (temp.piece_type == BLOCK_BLANK) {
                lv_obj_add_style(brd_lv_obj_t[i*j]  , LV_BTN_PART_MAIN, &style_blank);
                    printf("#");
                }
                // lv_obj_invalidate(brd_lv_obj_t[i*j]);
            }
        }
        printf("\n");

        lv_task_handler();
        
        
    }
}


static void lv_tick_task(void *arg) {
    (void) arg;

    lv_tick_inc(LV_TICK_PERIOD_MS);
}
