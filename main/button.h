#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#ifndef BUTTON_H
#define BUTTON_H


#define BTN_DP_RIGHT  GPIO_NUM_13
#define BTN_DP_LEFT  GPIO_NUM_14     
#define BTN_DP_DOWN  GPIO_NUM_27  
#define BTN_DP_UP GPIO_NUM_26 
#define BTN_A  GPIO_NUM_21
#define BTN_B  GPIO_NUM_32 
#define BTN_X  GPIO_NUM_33 
#define BTN_Y  GPIO_NUM_25

gpio_num_t button_pins[8] = {BTN_DP_RIGHT, BTN_DP_DOWN, BTN_DP_LEFT, BTN_DP_UP, BTN_A, BTN_B, BTN_X, BTN_Y};

void init_buttons();
int read_button(gpio_num_t pin);

#endif