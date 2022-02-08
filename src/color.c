#include <curses.h>

#include "color.h"

void
set_border_color()
{
	int foreground_color = COLOR_WHITE;
	int background_color = COLOR_BLACK;

	init_pair(border_color_pair, foreground_color, background_color);
	attrset(COLOR_PAIR(border_color_pair));
}
