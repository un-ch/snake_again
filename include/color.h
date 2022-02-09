#ifndef COLOR_H_SENTRY
#define COLOR_H_SENTRY

enum { border_color_pair = 6 };

enum all_colors {
	white_on_black,
	magenta_on_black,
	green_on_black,
	red_on_black,
	yellow_on_black,
	black_on_black
};

void
set_color(int all_colors);

#endif
