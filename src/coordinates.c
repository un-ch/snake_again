#include <ncurses.h>
#include <stdlib.h>

#include "coordinates.h"
#include "end_program.h"
#include "get_random_number.h"

void
set_random_coordinates(struct coordinates *crd)
{
	int min_x = 1;
	int min_y = 1;
	int max_x, max_y;

	getmaxyx(stdscr, max_y, max_x);

	/*
	* We assume that it is not possible to display symbols
	* at the (max_y, max_x) screen coordinates.
	* The borders around the game field occupy the (max_y - 1, max_x - 1)
	* coordinates.
	* Therefore, objects inside the borders should have the following
	* maximum values:
	*/

	max_x -= 2;
	max_y -= 2;

	crd->x = get_random_int_number(min_x, max_x);
	crd->y = get_random_int_number(min_y, max_y);
}

int
are_equal_coordinates(const struct coordinates *a,
			const struct coordinates *b)
{
	return ((a->x == b->x) && (a->y == b->y));
}

struct coordinates_list *
fill_in_coordinates_random(const int max_iterator,
				const struct coordinates *head)
{
	struct coordinates_list *first = NULL, *temp;
	int i;

	for (i = 0; i < max_iterator; i++) {
		temp = NULL;
		temp = malloc(sizeof(struct coordinates_list));

		if (!temp) {
			end(malloc_err);
		}

		do {
			set_random_coordinates(&temp->coord);
		} while (are_equal_coordinates(&temp->coord, head));

		temp->next = first;
		first = temp;
	}

	return first;
}

void
delete_coordinate_list(struct coordinates_list **list)
{
	while (*list) {
		struct coordinates_list *temp = (*list);
		(*list) = (*list)->next;
		free(temp);
	}

	(*list) = NULL;
}

void
reset_direction(struct coordinates **crd)
{
	(*crd)->x = 0;
	(*crd)->y = 0;
}

void
init_direction(struct coordinates **crd)
{
	(*crd) = NULL;
	(*crd) = malloc(sizeof(struct coordinates));

	if (!(*crd)) {
		end(malloc_err);
	}

	reset_direction(crd);
}
