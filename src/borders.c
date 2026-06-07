#include <ncurses.h>

#include "borders.h"
#include "color.h"
#include "string.h"

void
display_borders_with_game_title(void)
{
	const char game_title[] = "Snake Again";
	int max_screen_width, str_length;
	int height = 0;
	int width;

	set_color(gray_on_black);
	box(stdscr, 0, 0);

	max_screen_width = getmaxx(stdscr);
	str_length = string_length(game_title);
	width = (max_screen_width - str_length) / 2;

	mvwprintw(stdscr, height, width, " %s ", game_title);
}

int
border_collision(const struct coordinates *head)
{
	int max_x, max_y;
	int rc = 0;
	int min_x = 1;
	int min_y = 1;

	getmaxyx(stdscr, max_y, max_x);
	max_y -= 2;
	max_x -= 2;

	if ((head->x < min_x) ||
	    (head->x > max_x) ||
	    (head->y < min_y) ||
	    (head->y > max_y)) {
		rc = 1;
	}

	return rc;
}
