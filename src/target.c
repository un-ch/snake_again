#include <stdlib.h>	/* for free() */
#include <stdbool.h>

#include "target.h"
#include "coordinates.h"
#include "objects.h"

bool
is_contact_with_target(const struct coordinates snake_head,
			struct coordinates_list *target)
{
	struct coordinates_list **pp = &target;
	int result = false;

	while (*pp) {
		if (is_equal_coordinates(snake_head, (*pp)->coord)) {
			struct coordinates_list *temp = *pp;
			*pp = (*pp)->next;
			free(temp);
			result = true;
			break;
		}
		pp = &(*pp)->next;
	}

	return result;
}

void
display_target_in_fog_of_war(struct coordinates snake,
			struct coordinates_list *target)
{
	struct coordinates_list *temp = target;
	int x_max, x_min, y_max, y_min;

	x_max = snake.x + 5;
	x_min = snake.x - 5;
	y_max = snake.y + 5;
	y_min = snake.y - 5;
	
	while (temp) {
		if ((temp->coord.x < x_max) &&
		    (temp->coord.y < y_max) &&
		    (temp->coord.x > x_min) &&
		    (temp->coord.y > y_min)) {
			display_object(target_obj, temp->coord);
		}

		temp = temp->next;
	}
}

void
display_target(struct coordinates_list *target)
{
	struct coordinates_list *temp = target;

	while (temp) {
		show_object_target(temp->coord);
		temp = temp->next;
	}
}
