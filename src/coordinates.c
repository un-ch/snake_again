
#include <ncurses.h>
#include <stdlib.h>		/* for malloc */

#include "coordinates.h"
#include "get_random_number.h"

void
set_random_coordinates(struct coordinates *coord)
{
	int max_x, max_y;
	getmaxyx(stdscr, max_y, max_x);
	coord->x = get_random_int_number(max_x);
	coord->y = get_random_int_number(max_y);
}

int
is_equal_coordinates(const struct coordinates coord,
					const struct coordinates pattern)
{
	int result;
	result = TRUE;

	if(coord.x != pattern.x || coord.y != pattern.y)
		result = FALSE;
	return result;
}

struct coordinates_list *
fill_in_coordinates_random(const int max_iterator,
						const struct coordinates snake_head_coordinate)
{
	struct coordinates_list *first = NULL, *temp;
	int i;

	for(i = 0; i < max_iterator; i++) {
		temp = malloc(sizeof(struct coordinates_list));
		do {
			set_random_coordinates(&temp->coord);
		} while (is_equal_coordinates(temp->coord, \
									snake_head_coordinate));
		temp->next = first;
		first = temp;
	}
	return first;
}

int
is_contact_with_borders(const struct coordinates snake_head_coordinate)
{
	int result, max_x, max_y;

	getmaxyx(stdscr, max_y, max_x);
	result = FALSE;

	if((snake_head_coordinate.x < 0) ||
		(snake_head_coordinate.x > max_x) ||
		(snake_head_coordinate.y) < 0 ||
		(snake_head_coordinate.y > max_y))
		result = TRUE;

	return result;
}
