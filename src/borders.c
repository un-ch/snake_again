#include <ncurses.h>

#include "borders.h"

void
display_borders()
{
	init_pair(borders_color_pair, COLOR_CYAN, COLOR_BLACK);
	attrset(COLOR_PAIR(borders_color_pair));
	box(stdscr, 0, 0);
}

int
is_contact_with_borders(const struct coordinates snake_head)
{
	int result = false_exit_code;
	int min_x = 1;
	int min_y = 1;
	int max_x, max_y;

	getmaxyx(stdscr, max_y, max_x);
	max_y -= 2;
	max_x -= 2;

	if((snake_head.x < min_x) ||
		(snake_head.x > max_x) ||
		(snake_head.y < min_y) ||
		(snake_head.y > max_y)) {

		result = true_exit_code;
	}

	return result;
}
