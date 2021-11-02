#include <stdlib.h>

#include "snake_object.h"
#include "coordinate.h"
#include "objects.h"

void
move_snake_object(struct coordinate_deque *snake,
					struct coordinate direction)
{
	struct coordinate_doubly_list *temp;

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
add_new_snake_element(struct coordinate_deque *snake,
								struct coordinate c)
{
	struct coordinate_doubly_list *temp;

	temp = malloc(sizeof(struct coordinate_doubly_list));
	temp->coord.x = c.x;
	temp->coord.y = c.y;
	temp->prev = snake->last;
	temp->next = NULL;
	if(snake->last == NULL)
		snake->first = temp;
	else
		snake->last->next = temp;
	snake->last = temp;
}
