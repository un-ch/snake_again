#include <curses.h>

#include "color.h"

void
set_color(enum fgr_bgr_colors colors)
{
	switch(colors) {
		case black_on_black:
			init_pair(black_on_black, COLOR_BLACK, COLOR_BLACK);
			attrset(COLOR_PAIR(black_on_black));
			break;
		case white_on_white:
			init_pair(white_on_white, COLOR_WHITE, COLOR_WHITE);
			attrset(COLOR_PAIR(white_on_white));
			break;
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
		case yellow_on_black:
			init_pair(yellow_on_black, COLOR_YELLOW, COLOR_BLACK);
			attrset(COLOR_PAIR(yellow_on_black));
			break;
		case black_on_white:
			init_pair(black_on_white, COLOR_BLACK, COLOR_WHITE);
			attrset(COLOR_PAIR(black_on_white));
			break;
		case red_on_white:
			init_pair(red_on_white, COLOR_RED, COLOR_WHITE);
			attrset(COLOR_PAIR(red_on_white));
			break;
	}
}
