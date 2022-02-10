#ifndef COLOR_H_SENTRY
#define COLOR_H_SENTRY

enum fgr_bgr_colors {
	black_on_black		= 1,
	magenta_on_black	= 2,
	green_on_black		= 3,
	red_on_black			= 4,
	yellow_on_black		= 5,
	white_on_black		= 6
};

void
set_color(enum fgr_bgr_colors colors);

#endif
