#include <stdlib.h>		/* for free() */

#include "target.h"
#include "coordinate.h"

int
is_contact_with_target(const struct coordinate c,
					struct coordinate_list *target)
{
	struct coordinate_list **pp = &target;
	int result = FALSE;

	while(*pp) {
		if(is_equal_coordinate(c, (*pp)->coord)) {
			struct coordinate_list *temp = *pp;
			*pp = (*pp)->next;
			free(temp);
			result = TRUE;
			break;
		}
		pp = &(*pp)->next;
	}
	return result;
}

void
display_target_in_fog_of_war(struct coordinate snake,
							struct coordinate_list *tar,
{
	struct coordinate_list *temp;
	int x_max, x_min, y_max, y_min;

	x_max = snake.x + 5;
	x_min = snake.x - 5;
	y_max = snake.y + 5;
	y_min = snake.y - 5;
	for(temp = obj; temp; temp = temp->next) {
		if((temp->coord.x < x_max) &&
			(temp->coord.y < y_max) &&
			(temp->coord.x > x_min) &&
			(temp->coord.y > y_min)) {
				show_object_target(temp->coord);
			}
	}
}
