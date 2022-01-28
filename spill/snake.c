#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>

#include "snake.h"
#include "constants.h"

/*Making the base based on linked list code that we borrowed from the internet:*/

int get_square_value(int x, int y);
int set_square_value(int x, int y, int value);
void place_random_food(int* count_food);
void place_food_at_coords(int x, int y, int* count_foot);

/* Add new Body element on top of head. */
void push(struct Body** head_ref, short int new_x, short int new_y)
{
    /* 1. allocate node */
    struct Body* new_node = (struct Body*)malloc(sizeof(struct Body));
 
    /* 2. set x and y. Push adds to the front of the list so new node is the head, therefore set isHead is 1  */
    new_node->x = new_x;
    new_node->y = new_y;
    new_node->isHead = 1;
 
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
}

/* Given a node as prev_node, insert a new node after the given node*/
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
    short int new_x = old_x + direction_x;
    short int new_y = old_y + direction_y;

    short int next_value = get_square_value(new_x, new_y);

    if (next_value == BLOCK_SNAKE) {
        return;
    }

    // Create new head
    push(&head, new_x, new_y);
    set_square_value(new_x, new_y, BLOCK_SNAKE);

    // Remove tail (do not do this if snake eats!)
    if (next_value != BLOCK_FOOD) {
        tail->prev->next = NULL;
        set_square_value(tail->x, tail->y, BLOCK_BLANK);
    } else {
        if (*count_food <= 1) {
            place_random_food(count_food);
        } else {
            (*count_food)--;
        }
    }

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
    struct Body* bodypart = (*node);
    struct Body* current = (*node);

    //struct Body prev = *bodypart->prev;

    //prev.next = NULL;
    
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

void printList(struct Body* node)
{
    struct Body* last;
    printf("\nTraversal in forward direction \n");
    while (node != NULL) {
        printf(" %d ", node->x);
        printf(" %d ", node->y);
        printf(" %d ", node->isHead);
        printf("|");
        last = node;
        node = node->next;
    }
 
    printf("\nTraversal in reverse direction \n");
    while (last != NULL) {
        printf(" %d ", last->x);
        printf(" %d ", last->y);
        printf(" %d ", last->isHead);
        printf("|");
        last = last->prev;
    }
}

struct Snake create_snake(void) {
    struct Body* head = NULL;
    push(&head, 0, 0);
    push(&head, 1, 0);
    push(&head, 2, 0);
    push(&head, 3, 0);
    push(&head, 4, 0);
    push(&head, 5, 0);

    struct Snake snake = {
        .id = 0, .direction_x = 1, .direction_y = 0, .head = head, .isAlive = true
    };

    set_direction(&snake, DIRECTION_RIGHT);

    return snake;
}

/*int main()
{
    struct Body* head = NULL;
    push(&head, 0, 0);
 
    push(&head, 10, 10);
 
    push(&head, 20, 20);
 
    insertAfter(head, 5, 5);
    append(&head, -10, -10);
 
    printf("Created DLL is: ");
    printList(head);
    move(&head, 50, 50, false);
    printList(head);
 
    getchar();
    return 0;
}*/