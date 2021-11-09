#include <ncurses.h>

#include "borders.h"

void
display_borders()
{
	init_pair(borders_color_pair, COLOR_CYAN, COLOR_BLACK);
	attrset(COLOR_PAIR(borders_color_pair));
	box(stdscr, 0, 0);
}
