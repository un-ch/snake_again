#include <ncurses.h>

#include "screen.h"
#include "objects.h"
#include "borders.h"
#include "color.h"

void
clear_screen()
{
	int max_screen_height, max_screen_width;
	int screen_height = 1;
	int screen_width = 1;

	clear();
	refresh();
	display_borders_with_game_title();

	getmaxyx(stdscr, max_screen_height, max_screen_width);
	set_color(white_on_white);

	for(; screen_height < (max_screen_height - 1); screen_height++) {
		for(screen_width = 1; screen_width < (max_screen_width - 1); screen_width++) {
			move(screen_height, screen_width);
			addch(symbol_blank);
		}
	}
}
