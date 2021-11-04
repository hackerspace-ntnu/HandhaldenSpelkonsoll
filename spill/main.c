#include "snake.h"
#include "board.h"

void main() {
    init_board();
    struct Body* snake_head = create_snake();
    add_snake_to_board(snake_head);
}