#include <stdlib.h>

#include "target.h"
#include "coordinates.h"
#include "objects.h"

int
target_collision(const struct coordinates head,
			struct coordinates_list **target)
{
	struct coordinates_list **pp = target;
	int rc = 0;

	while (*pp) {
		if (are_equal_coordinates(head, (*pp)->coord)) {
			struct coordinates_list *temp = *pp;
			*pp = (*pp)->next;
			free(temp);
			rc = 1;
			break;
		}
		pp = &(*pp)->next;
	}

	return rc;
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
