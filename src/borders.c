#include <ncurses.h>

#include "borders.h"
#include "string.h"
#include "color.h"

void
display_borders_with_game_title()
{

	const char game_title[] = "Snake Again";
	int max_screen_width;
	int str_length;
	int cursor_width_coordinate;
	int cursor_height_coordinate = 0;

	set_color(black_on_white);
	box(stdscr, 0, 0);

	max_screen_width = getmaxx(stdscr);
	str_length = string_length(game_title);
	cursor_width_coordinate = (max_screen_width - str_length) / 2;

	mvwprintw(stdscr, cursor_height_coordinate, cursor_width_coordinate,\
																									" %s ", game_title);
}

int
is_contact_with_borders(const struct coordinates snake_head)
{
	int result = FALSE;
	int min_x = 1;
	int min_y = 1;
	int max_x, max_y;

	getmaxyx(stdscr, max_y, max_x);
	max_y -= 2;
	max_x -= 2;

	if((snake_head.x < min_x)
		|| (snake_head.x > max_x)
		|| (snake_head.y < min_y)
		|| (snake_head.y > max_y)) {
		result = TRUE;
	}

	return result;
}
