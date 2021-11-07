
#include <ncurses.h>
#include <stdlib.h>		/* for malloc */

#include "coordinates.h"
#include "get_random_number.h"

void
set_random_coordinates(struct coordinates *crd)
{
	int max_x, max_y;
	getmaxyx(stdscr, max_y, max_x);
	crd->x = get_random_int_number(max_x);
	crd->y = get_random_int_number(max_y);
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

int
is_contact_with_borders(const struct coordinates snake_head)
{
	int result = FALSE;
	int max_x, max_y;

	getmaxyx(stdscr, max_y, max_x);

	if((snake_head.x < 0) ||
		(snake_head.x > max_x) ||
		(snake_head.y) < 0 ||
		(snake_head.y > max_y)) {

		result = TRUE;
	}

	return result;
}
