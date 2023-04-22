#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h> 

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define SCREEN_HEIGHT 320
#define SCREEN_WIDTH 480
#define BLOCK_SIZE 40

#define PLAYER_NUMBER 1 // Number of players in the game
#define MAX_FOOD_AT_ONCE 1 //Will be adjusted on amount of players later
#define WRAPPING_ENABLED 1

#define MULTIPLAYER_BUFFER_SIZE 256
#define IS_HOST 1

#define BOARD_HEIGHT (SCREEN_HEIGHT/BLOCK_SIZE)
#define BOARD_WIDTH (SCREEN_WIDTH/BLOCK_SIZE)

#define BLOCK_BLANK 0
#define BLOCK_FOOD 1
#define BLOCK_SNAKE 2

#define WRAPPING_ENABLED 1

#define DIRECTION_UP 0
#define DIRECTION_RIGHT 1
#define DIRECTION_DOWN 2
#define DIRECTION_LEFT 3

#endif
