
#include <ncurses.h>

#include "coordinate.h"
#include "get_random_number.h"

void
set_random_coordinate(struct coordinate *coord)
{
	int max_x, max_y;
	getmaxyx(stdscr, max_y, max_x);
	coord->x = get_random_int_number(max_x);
	coord->y = get_random_int_number(max_y);
}

int
is_equal_coordinate(const struct coordinate coord,
					const struct coordinate pattern)
{
	int result;
	result = TRUE;

	if(coord.x != pattern.x || coord.y != pattern.y)
		result = FALSE;
	return result;
}

