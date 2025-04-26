#ifndef COLOR_H_SENTRY
#define COLOR_H_SENTRY

enum fgr_bgr_colors {
	black_on_black		= 1,
	white_on_white		= 2,
	magenta_on_black	= 3,
	green_on_black		= 4,
	red_on_black			= 5,
	yellow_on_black		= 6,
	white_on_black		= 7,
	black_on_white		= 8,
	red_on_white			= 9
};

void
set_color(enum fgr_bgr_colors colors);

#endif
