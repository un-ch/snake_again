#include <ncurses.h>

#include "dot_background.h"
#include "color.h"
#include "screen.h"
#include "objects.h"
#include "coordinates.h"

void
display_dot_background()
{
	int max_screen_height, max_screen_width;
	/* int min_screen_height, min_screen_width; */
	int screen_height = 1;
	int screen_width = 1;
	struct coordinates crd;

	getmaxyx(stdscr, max_screen_height, max_screen_width);
	set_color(black_on_white);

	for(; screen_height < (max_screen_height - 1); ++screen_height) {
		for(screen_width = 1; screen_width < (max_screen_width - 1); ++screen_width) {
			crd.y = screen_height;
			crd.x = screen_width;
			display_object(crd, dot);
		}
	}
}

void
display_dot_background_in_fog_of_war(const struct coordinates snake)
{
	int x_max, x_min, y_max, y_min;
	int screen_height, screen_width;

	x_max = snake.x + 5;
	x_min = snake.x - 5;
	y_max = snake.y + 5;
	y_min = snake.y - 5;

	screen_height = y_min;
	screen_width = x_min;

	for(; screen_height < (y_max - 1); ++screen_height) {
		for(screen_width = x_min; screen_width < (x_max - 1); ++screen_width) {
			move(screen_height, screen_width);
			addch(symbol_dot);
		}
	}
}
