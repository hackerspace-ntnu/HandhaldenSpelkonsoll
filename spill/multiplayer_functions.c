//#include "snake.h"

void get_multiplayer_struct(struct multiplayer_info *multi_info, struct multiplayer_info **multi_info_buffer, int *stack_pointer){
    if(multi_info->id > 3){ // Our snakes have ids in the 0-4 range
        printf("Unknown snake id: %d", multi_info->id);
    }
    if (*stack_pointer < MULTIPLAYER_BUFFER_SIZE){
        multi_info_buffer[*stack_pointer] = multi_info;
        *stack_pointer++;
    }    
    else{
        printf("No more space on stack, struct dropped\n");
    }
}