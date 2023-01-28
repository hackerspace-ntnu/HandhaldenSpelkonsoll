#include "constants.h"
#include "snake.h"
#include "board.h" 

/*Making the base based on linked list code that we borrowed from the internet:*/

/* Add new Body element on top of head. */
void push(board_piece_t** board, body_t** head_ref, snake_t* snake, short int new_x, short int new_y)
{
    /* 1. allocate node */
    body_t* new_node = (body_t*)malloc(sizeof(body_t));
 
    /* 2. set x and y. Push adds to the front of the list so new node is the head, therefore set isHead is 1  */
    new_node->x = new_x;
    new_node->y = new_y;
    new_node->isHead = 1;
    new_node->snake = snake;
 
    /* 3. Make next of new node as head and previous as NULL */
    new_node->next = (*head_ref);
    new_node->prev = NULL;
 
    /* 4. change prev of head node to new node */
    if ((*head_ref) != NULL) {
        (*head_ref)->prev = new_node;
        /* The previous head is now a part of the body, therefore isHead is 0 */
        (*head_ref)->isHead = 0;
    }
 
    /* 5. move the head to point to the new node */
    (*head_ref) = new_node;

    set_square_value(board, new_x, new_y, BLOCK_SNAKE, new_node);
}

/* Given a node as prev_node, insert a new node after it*/
//(Put node behind prev_node)
void insertAfter(board_piece_t** board, body_t* prev_node, short int new_x, short int new_y)
{
	/*1. check if the given prev_node is NULL */
	if (prev_node == NULL) {
		printf("the given previous node cannot be NULL");
		return;
	}

	/* 2. allocate new node */
	body_t* new_node = (body_t*)malloc(sizeof(body_t));

	/* 3. put in the data */
	new_node->x = new_x;
	new_node->y = new_y;
	new_node->isHead = 0;

	/* 4. Make next of new node as next of prev_node */
	new_node->next = prev_node->next;

	/* 5. Make the next of prev_node as new_node */
	prev_node->next = new_node;

	/* 6. Make prev_node as previous of new_node */
	new_node->prev = prev_node;

	/* 7. Change previous of new_node's next node */
	if (new_node->next != NULL)
		new_node->next->prev = new_node;
    
    set_square_value(board, new_x, new_y, BLOCK_SNAKE, new_node);
}

/* Given a reference (pointer to pointer) to the head
of a DLL and an int, appends a new node at the end.
AKA puts more booty on Susan Ibaka*/
void append(board_piece_t** board, body_t** head_ref, short int new_x, short int new_y)
{
	/* 1. allocate node */
	body_t* new_node = (body_t*)malloc(sizeof(body_t));

	body_t* last = *head_ref; /* used in step 5 */

	/* 2. put in the data */
	new_node->x = new_x;
	new_node->y = new_y;
	new_node->isHead = 0;

	/* 3. This new node is going to be the last node, so
		make next of it as NULL */
	new_node->next = NULL;

	/* 4. If the Linked List is empty, then make the new
		node as head */
	if (*head_ref == NULL) {
		new_node->prev = NULL;
        new_node->isHead =1;
		*head_ref = new_node;
		return;
	}

	/* 5. Else traverse till the last node */
	while (last->next != NULL)
		last = last->next;

	/* 6. Change the next of last node */
	last->next = new_node;

	/* 7. Make last node as previous of new node */
	new_node->prev = last;

    set_square_value(board, new_x, new_y, BLOCK_SNAKE, new_node);

	return;
}

body_t* get_head(body_t* bodypart) {
    if (bodypart->prev != NULL) {
        return get_head(bodypart->prev);
    }
    return bodypart;
}

body_t* get_tail(body_t* bodypart) {
    if (bodypart->next != NULL) {
        return get_tail(bodypart->next);
    }
    return bodypart;
}

void move(board_piece_t** board, snake_t* snake, body_t** node, short int direction_x, short int direction_y, int* count_food) {
    if (!snake->isAlive) {
        return;
    }
    // Get relevant body parts
    body_t* head = get_head(*node);
    body_t* neck = head->next;
    body_t* tail = get_tail(*node);

    // Get coordinates of the old head
    short int old_x = head->x;
    short int old_y = head->y;

    // Calculate new coordinates
    short int new_x = old_x + snake->direction_x;
    short int new_y = old_y + snake->direction_y;

    // Checks if new head will be inside a wall
    // If clipping is turned on, head will be put on the opposite side of the field
    // If clipping is turned off, the snake dies
    printf("Calculated new position\n");
    if (new_x > (BOARD_WIDTH - 1)) {
        new_x = 0;
        if (!WRAPPING_ENABLED){
            split_snake(board, snake, &head, count_food);
            snake->isAlive = false;
            return;
        }
    }
    else if (new_x < 0) {
        new_x = BOARD_WIDTH - 1;
        if (!WRAPPING_ENABLED) {
            split_snake(board, snake, &head, count_food);
            snake->isAlive = false;
            return;
        }
    }
    else if (new_y > (BOARD_HEIGHT-1)) {
        new_y = 0;
        if (!WRAPPING_ENABLED) {
            split_snake(board, snake, &head, count_food);
            snake->isAlive = false;
            return;
        }
    }
    else if (new_y < 0) {
        new_y = BOARD_HEIGHT - 1;
        if (!WRAPPING_ENABLED) {
            split_snake(board, snake, &head, count_food);
            snake->isAlive = false;
            return;
        }
    }

    printf("Poyo\n");
    // Prevents snake from moving into its own neck
    if(neck != NULL){
       if ((new_x == neck->x) & (new_y == neck->y)){
            printf("Don't eat your own neck >:^(\n");
            return;
        } 
    }

    printf("Wah\n");
    // Get the value of the next square where the snake would move to,
    // and determine whether that square is a body part
    board_piece_t next_piece = get_square_value(board, new_x, new_y);
    bool next_is_body_part = next_piece.piece_type == BLOCK_SNAKE;
    
    printf("Next square is %s\n", next_is_body_part ? "body" : "not body");
    if (next_is_body_part) {
        body_t* part = next_piece.part;

        // If snake collides with itself: Die.
        if (part->snake->id == snake->id) {
            split_snake(board, snake, &head, count_food);
            snake->isAlive = false;
            printf("self collision\n");
            return;
        }

        // Get the length of each snake
        int length_this = get_snake_length(snake->head);
        int length_other = get_snake_length(part);

        if (part->isHead) {
            if (length_this == length_other) {
                snake->isAlive = false;
                part->snake->isAlive = false;
                split_snake(board, part->snake, &part, count_food);
                split_snake(board, snake, &head, count_food);
                return;
            } else if (length_this > length_other) {
                part->snake->isAlive = false;
                split_snake(board, part->snake, &part, count_food);
            } else {
                snake->isAlive = false;
                split_snake(board, snake, &head, count_food);
                return;
            }
        } else {
            split_snake(board, part->snake, &part, count_food);
        }
    }

    // Remove tail (do not do this if snake eats!)
    int single_piece_snake = tail->prev == NULL;
    if (next_piece.piece_type == BLOCK_FOOD || next_is_body_part) {
        if (*count_food <= 1) {
            place_random_food(board, count_food);
        } else {
            (*count_food)--;
        }
    } else {
        //printf("is tail null: %s\n", tail == NULL ? "yes" : "no");
        if (!single_piece_snake){
            tail->prev->next = NULL;
        }
        set_square_value(board, tail->x, tail->y, BLOCK_BLANK, NULL);
    }

    // Create new head
    push(board, &head, snake, new_x, new_y);
    set_square_value(board, new_x, new_y, BLOCK_SNAKE, head);

    if(single_piece_snake){
        head->next = NULL;
    }

    // Update ref
    *node = head;
}

void set_direction(snake_t* snake, int direction) {
    switch (direction)
    {
    case DIRECTION_UP:
        snake->direction_x = 0;
        snake->direction_y = -1;
        break;
    case DIRECTION_RIGHT:
        snake->direction_x = 1;
        snake->direction_y = 0;
        break;
    case DIRECTION_DOWN:
        snake->direction_x = 0;
        snake->direction_y = 1;
        break;
    case DIRECTION_LEFT:
        snake->direction_x = -1;
        snake->direction_y = 0;
        break;
    default:
        break;
    }
}

void split_snake(board_piece_t** board, snake_t* snake, body_t** node, int* count_food) {
    body_t* bodypart = *node;
    body_t* current = *node;
    
    while (current->next != NULL) {
        place_food_at_coords(board, current->x, current->y, count_food);
        current = current->next;
    };
    place_food_at_coords(board, current->x, current->y, count_food);

    if (bodypart->isHead) {
        snake->isAlive = false;
        return;
    }

    bodypart->next = NULL;
    bodypart->prev->next = NULL;
}

int get_snake_length(body_t* head) {
    body_t* current = head;
    int length = 1;

    while (current->next != NULL) {
        length++;
        current = current->next;
    };

    return length;
}

snake_t create_snake(board_piece_t** board, int length, int coords[][2], int* snake_id_counter) {
    body_t* head = NULL;

    snake_t* snake = (snake_t*)malloc(sizeof (snake_t));

    snake->id = *snake_id_counter;
    snake->direction_x = 1;
    snake->direction_y = 0;
    snake->isAlive = true;

    (*snake_id_counter)++;

    for (int i = 0; i < length; i++) {
        push(board, &head, snake, coords[i][0], coords[i][1]);
    }

    snake->head = head;

    set_direction(snake, DIRECTION_RIGHT);

    return *snake;
}
