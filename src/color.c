#include "color.h"
#include <ncurses.h>
#include "end_program.h"

void
set_color(enum fgr_bgr_colors colors)
{
	short fg, bg;

	if (!has_colors()) {
		end(monochrome_display);
	}

	switch(colors) {
	case black_on_black:
		fg = COLOR_BLACK;
		bg = COLOR_BLACK;
		break;
	case white_on_white:
		fg = COLOR_WHITE;
		bg = COLOR_WHITE;
		break;
	case white_on_black:
		fg = COLOR_WHITE;
		bg = COLOR_BLACK;
		break;
	case magenta_on_black:
		fg = COLOR_MAGENTA;
		bg = COLOR_BLACK;
		break;
	case green_on_black:
		fg = COLOR_GREEN;
		bg = COLOR_BLACK;
		break;
	case red_on_black:
		fg = COLOR_RED;
		bg = COLOR_BLACK;
		break;
	case yellow_on_black:
		fg = COLOR_YELLOW;
		bg = COLOR_BLACK;
		break;
	case black_on_white:
		fg = COLOR_BLACK;
		bg = COLOR_WHITE;
		break;
	case red_on_white:
		fg = COLOR_RED;
		bg = COLOR_WHITE;
		break;
	case gray_on_black:
		fg = color_gray;
		bg = COLOR_BLACK;
		break;
	case cyan_on_black:
		fg = COLOR_CYAN;
		bg = COLOR_BLACK;
		break;
	default:
		break;
	}

	init_pair(colors, fg, bg);
	attrset(COLOR_PAIR(colors));
}
