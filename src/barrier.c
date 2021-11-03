#include "barrier.h"
#include "coordinate.h"

int
is_contact_with_barrier(const struct coordinate c,
				const struct coordinate_list *barrier)
{
	const struct coordinate_list *temp = barrier;
	int result;
	result = FALSE;

	for(; temp; temp = temp->next) {
		if(is_equal_coordinate(c, temp->coord)) {
			result = TRUE;
			break;
		}
	}
	return result;
}

void
display_barrier_in_fog_of_war(struct coordinate snake,
							struct coordinate_list *bar)
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
				show_object_barrier(temp->coord);
			}
	}
}
