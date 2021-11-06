#include <stdlib.h>

#include "snake_object.h"
#include "coordinates.h"
#include "objects.h"

void
move_snake_object(struct coordinates_deque *snake,
					struct coordinates direction)
{
	struct coordinates_doubly_list *temp;

	temp = snake->first;

	if(direction.x == 0 && direction.y == 0) {
		for(; temp; temp = temp->next) {
			show_object_snake(temp->coord);
		}
		return;
	}

	for(; temp; temp = temp->next) {
		hide_object(temp->coord);
	}

	temp = snake->last;
	for(; temp->prev; temp = temp->prev) {
		temp->coord.x = temp->prev->coord.x;	
		temp->coord.y = temp->prev->coord.y;	
	}

	snake->first->coord.x += direction.x; 
	snake->first->coord.y += direction.y; 

	temp = snake->first;
	for(; temp; temp = temp->next) {
		show_object_snake(temp->coord);	
	}
}

void
add_new_snake_element(struct coordinates_deque *snake,
								struct coordinates crd)
{
	struct coordinates_doubly_list *temp;

	temp = malloc(sizeof(struct coordinates_doubly_list));
	temp->coord.x = crd.x;
	temp->coord.y = crd.y;
	temp->prev = snake->last;
	temp->next = NULL;
	if(snake->last == NULL)
		snake->first = temp;
	else
		snake->last->next = temp;
	snake->last = temp;
}
