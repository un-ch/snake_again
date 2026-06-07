#include "barrier.h"
#include "coordinates.h"
#include "objects.h"

int
barrier_collision(const struct coordinates *head,
			const struct coordinates_list *barrier)
{
	int rc = 0;
	const struct coordinates_list *temp = barrier;

	while (temp) {
		rc = are_equal_coordinates(head, &temp->coord);
		if (rc != 0)
			break;

		temp = temp->next;
	}

	return rc;
}

void
display_barrier_in_fog_of_war(const struct coordinates head,
				const struct coordinates_list *barrier)
{
	const struct coordinates_list *temp = barrier;
	int x_max, x_min, y_max, y_min;

	x_max = head.x + fog_radius;
	x_min = head.x - fog_radius;
	y_max = head.y + fog_radius;
	y_min = head.y - fog_radius;

	while (temp) {
		if ((temp->coord.x < x_max) &&
		    (temp->coord.y < y_max) &&
		    (temp->coord.x > x_min) &&
		    (temp->coord.y > y_min)) {

			show_object_barrier(temp->coord);
		}

		temp = temp->next;
	}
}

void
display_barrier(const struct coordinates_list *barrier)
{
	const struct coordinates_list *temp = barrier;

	while (temp) {
		show_object_barrier(temp->coord);
		temp = temp->next;
	}
}
