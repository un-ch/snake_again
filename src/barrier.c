#include "barrier.h"
#include "coordinate.h"
#include "objects.h"

int
is_contact_with_barrier(const struct coordinate snake_head,
				const struct coordinate_list *barrier)
{
	const struct coordinate_list *temp = barrier;
	int result;
	result = FALSE;

	for(; temp; temp = temp->next) {
		if(is_equal_coordinate(snake_head, temp->coord)) {
			result = TRUE;
			break;
		}
	}
	return result;
}

void
display_barrier_in_fog_of_war(struct coordinate snake_head,
							struct coordinate_list *barrier)
{
	struct coordinate_list *temp = barrier;
	int x_max, x_min, y_max, y_min;

	x_max = snake_head.x + 5;
	x_min = snake_head.x - 5;
	y_max = snake_head.y + 5;
	y_min = snake_head.y - 5;
	for(; temp; temp = temp->next) {
		if((temp->coord.x < x_max) &&
			(temp->coord.y < y_max) &&
			(temp->coord.x > x_min) &&
			(temp->coord.y > y_min)) {
				show_object_barrier(temp->coord);
			}
	}
}

void
display_barrier(struct coordinate_list *barrier)
{
	struct coordinate_list *temp = barrier;

	while(temp) {
		show_object_barrier(temp->coord);
		temp = temp->next;
	}
}
