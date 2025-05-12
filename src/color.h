#ifndef COLOR_H
#define COLOR_H

enum {
	color_gray = 0b1000
};

enum fgr_bgr_colors {
	black_on_black,
	white_on_white,
	magenta_on_black,
	green_on_black,
	red_on_black,
	yellow_on_black,
	white_on_black,
	black_on_white,
	red_on_white,
	gray_on_black,
	cyan_on_black
};

void
set_color(enum fgr_bgr_colors colors);

#endif
