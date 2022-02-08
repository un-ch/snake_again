#include <curses.h>

#include "color.h"

void
set_color(int all_colors)
{
	switch(all_colors) {
		case white_on_black:
			init_pair(white_on_black, COLOR_WHITE, COLOR_BLACK);
			attrset(COLOR_PAIR(white_on_black));
			break;
		case magenta_on_black:
			init_pair(magenta_on_black, COLOR_MAGENTA, COLOR_BLACK);
			attrset(COLOR_PAIR(magenta_on_black));
			break;
		case green_on_black:
			init_pair(green_on_black, COLOR_GREEN, COLOR_BLACK);
			attrset(COLOR_PAIR(green_on_black));
			break;
		case red_on_black:
			init_pair(red_on_black, COLOR_RED, COLOR_BLACK);
			attrset(COLOR_PAIR(red_on_black));
			break;
		case black_on_black:
			init_pair(black_on_black, COLOR_BLACK, COLOR_BLACK);
			attrset(COLOR_PAIR(black_on_black));
			break;
	}
}
