#include <ncurses.h>
#include <stdlib.h>	/* for malloc */
#include <stdbool.h>
#include "coordinates.h"
#include "get_random_number.h"
#include "end_program.h"

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

bool
is_equal_coordinates(const struct coordinates c,
			const struct coordinates p)
{
	int result = true;

	if ((c.x != p.x) ||
	    (c.y != p.y)) {

		result = false;
	}

	return result;
}

struct coordinates_list *
fill_in_coordinates_random(const int max_iterator,
		const struct coordinates snake_head)
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
		} while (is_equal_coordinates(temp->coord, snake_head));

		temp->next = first;
		first = temp;
	}

	return first;
}

void
delete_coordinate_list(struct coordinates_list **list)
{
	while (*list) {
		struct coordinates_list *temp = *list;
		*list = (*list)->next;
		free(temp);
	}

	(*list) = NULL;
}

void
delete_coordinate_doubly_list(struct coordinates_doubly_list **list)
{
	while (*list) {
		struct coordinates_doubly_list *temp = *list;
		*list = (*list)->next;
		free(temp);
	}
	
	(*list) = NULL;
}
