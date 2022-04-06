/* #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h> */

/* #include "constants.h"
#include "snake.h"
#include "board.h" */

/*Making the base based on linked list code that we borrowed from the internet:*/
struct BoardPiece get_square_value(int x, int y);
void set_square_value(int x, int y, short int piece_type, struct Body* part);
void place_random_food(int* count_food);
void place_food_at_coords(int x, int y, int* count_food);

/* Add new Body element on top of head. */
void push(struct Body** head_ref, struct Snake* snake, short int new_x, short int new_y)
{
    /* 1. allocate node */
    struct Body* new_node = (struct Body*)malloc(sizeof(struct Body));
 
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

    set_square_value(new_x, new_y, BLOCK_SNAKE, new_node);
}

/* Given a node as prev_node, insert a new node after it*/
//(Put node behind prev_node)
void insertAfter(struct Body* prev_node, short int new_x, short int new_y)
{
	/*1. check if the given prev_node is NULL */
	if (prev_node == NULL) {
		printf("the given previous node cannot be NULL");
		return;
	}

	/* 2. allocate new node */
	struct Body* new_node = (struct Body*)malloc(sizeof(struct Body));

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
    
    set_square_value(new_x, new_y, BLOCK_SNAKE, new_node);
}

/* Given a reference (pointer to pointer) to the head
of a DLL and an int, appends a new node at the end.
AKA puts more booty on Susan Ibaka*/
void append(struct Body** head_ref, short int new_x, short int new_y)
{
	/* 1. allocate node */
	struct Body* new_node = (struct Body*)malloc(sizeof(struct Body));

	struct Body* last = *head_ref; /* used in step 5 */

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

    set_square_value(new_x, new_y, BLOCK_SNAKE, new_node);

	return;
}

struct Body* get_head(struct Body* bodypart) {
    if (bodypart->prev != NULL) {
        return get_head(bodypart->prev);
    }
    return bodypart;
}

struct Body* get_tail(struct Body* bodypart) {
    if (bodypart->next != NULL) {
        return get_tail(bodypart->next);
    }
    return bodypart;
}

void move(struct Snake* snake, struct Body** node, short int direction_x, short int direction_y, int* count_food) {
    if (!snake->isAlive) {
        return;
    }
    // Get relevant body parts
    struct Body* head = get_head(*node);
    struct Body* neck = head->next;
    struct Body* tail = get_tail(*node);

    // Get coordinates of the old head
    short int old_x = head->x;
    short int old_y = head->y;

    // Calculate new coordinates
    short int new_x = old_x + snake->direction_x;
    short int new_y = old_y + snake->direction_y;

    // Checks if new head will be inside a wall
    // If clipping is turned on, head will be put on the opposite side of the field
    // If clipping is turned off, the snake dies
    
    if (new_x > (BOARD_WIDTH - 1)) {
        new_x = 0;
        if (!WRAPPING_ENABLED){
            split_snake(snake, &head, count_food);
            snake->isAlive = false;
            return;
        }
    }
    else if (new_x < 0) {
        new_x = BOARD_WIDTH - 1;
        if (!WRAPPING_ENABLED) {
            split_snake(snake, &head, count_food);
            snake->isAlive = false;
            return;
        }
    }
    else if (new_y > (BOARD_HEIGHT-1)) {
        new_y = 0;
        if (!WRAPPING_ENABLED) {
            split_snake(snake, &head, count_food);
            snake->isAlive = false;
            return;
        }
    }
    else if (new_y < 0) {
        new_y = BOARD_HEIGHT - 1;
        if (!WRAPPING_ENABLED) {
            split_snake(snake, &head, count_food);
            snake->isAlive = false;
            return;
        }
    }

    // Get the value of the next square where the snake would move to,
    // and determine whether that square is a body part
    struct BoardPiece next_piece = get_square_value(new_x, new_y);
    bool next_is_body_part = next_piece.piece_type == BLOCK_SNAKE;
    
    if (next_is_body_part) {
        struct Body* part = next_piece.part;

        // If snake collides with itself: Die.
        if (part->snake->id == snake->id) {
            split_snake(snake, &head, count_food);
            snake->isAlive = false;
            return;
        }

        // Get the length of each snake
        int length_this = get_snake_length(snake->head);
        int length_other = get_snake_length(part);

        if (part->isHead) {
            if (length_this == length_other) {
                snake->isAlive = false;
                part->snake->isAlive = false;
                split_snake(part->snake, &part, count_food);
                split_snake(snake, &head, count_food);
                return;
            } else if (length_this > length_other) {
                part->snake->isAlive = false;
                split_snake(part->snake, &part, count_food);
            } else {
                snake->isAlive = false;
                split_snake(snake, &head, count_food);
                return;
            }
        } else {
            split_snake(part->snake, &part, count_food);
        }
    }

    // Remove tail (do not do this if snake eats!)
    if (next_piece.piece_type == BLOCK_FOOD || next_is_body_part) {
        if (*count_food <= 1) {
            place_random_food(count_food);
        } else {
            (*count_food)--;
        }
    } else {
        tail->prev->next = NULL;
        set_square_value(tail->x, tail->y, BLOCK_BLANK, NULL);
    }

    // Create new head
    push(&head, snake, new_x, new_y);
    set_square_value(new_x, new_y, BLOCK_SNAKE, head);

    // Update ref
    *node = head;
}

void set_direction(struct Snake* snake, int direction) {
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

void split_snake(struct Snake* snake, struct Body** node, int* count_food) {
    struct Body* bodypart = *node;
    struct Body* current = *node;
    
    while (current->next != NULL) {
        place_food_at_coords(current->x, current->y, count_food);
        current = current->next;
    };
    place_food_at_coords(current->x, current->y, count_food);

    if (bodypart->isHead) {
        snake->isAlive = false;
        return;
    }

    bodypart->next = NULL;
    bodypart->prev->next = NULL;
}

int get_snake_length(struct Body* head) {
    struct Body* current = head;
    int length = 1;

    while (current->next != NULL) {
        length++;
        current = current->next;
    };

    return length;
}

struct Snake create_snake(int length, int coords[][2], int* snake_id_counter) {
    struct Body* head = NULL;

    struct Snake* snake = (struct Snake*) malloc(sizeof (struct Snake));

    snake->id = *snake_id_counter;
    snake->direction_x = 1;
    snake->direction_y = 0;
    snake->isAlive = true;

    (*snake_id_counter)++;

    for (int i = 0; i < length; i++) {
        push(&head, snake, coords[i][0], coords[i][1]);
    }

    snake->head = head;

    set_direction(snake, DIRECTION_RIGHT);

    return *snake;
}
