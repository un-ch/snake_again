#include <ncurses.h>
#include <stdlib.h>		/* for malloc */

#include "coordinates.h"
#include "get_random_number.h"

void
set_random_coordinates(struct coordinates *crd)
{
	int min_x = 1;
	int min_y = 1;
	int max_x, max_y;

	getmaxyx(stdscr, max_y, max_x);

	/* we assume that there is no opportunity to display symbols
	 * in (max_y, max_x) screen coordinates;
	 * borders around the game field holds the (max_y-1, max_x-1)
	 * coordinates;
	 * so, objects inside the borders should have next maximum
	 * values:
	 */
	max_x -= 2;
	max_y -= 2;

	crd->x = get_random_int_number(min_x, max_x);
	crd->y = get_random_int_number(min_y, max_y);
}

int
is_equal_coordinates(const struct coordinates crd,
				const struct coordinates crd_pattern)
{
	int result = TRUE;

	if((crd.x != crd_pattern.x) ||
		(crd.y != crd_pattern.y)) {

		result = FALSE;
	}

	return result;
}

struct coordinates_list *
fill_in_coordinates_random(const int max_iterator,
				const struct coordinates snake_head)
{
	struct coordinates_list *first = NULL, *temp;
	int i = 0;

	for(; i < max_iterator; i++) {
		temp = malloc(sizeof(struct coordinates_list));

		do {
			set_random_coordinates(&temp->coord);
		} while (is_equal_coordinates(temp->coord, snake_head));

		temp->next = first;
		first = temp;
	}

	return first;
}

void
delete_coordinate_list(struct coordinates_list *list)
{
	while(list) {
		struct coordinates_list *temp = list;
		list = list->next;
		free(temp);
	}
}

void
delete_coordinate_doubly_list(struct coordinates_doubly_list **list)
{
	while(*list) {
		struct coordinates_doubly_list *temp = *list;
		*list = (*list)->next;
		free(temp);
	}
}
