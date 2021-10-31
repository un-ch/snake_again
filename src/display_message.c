
#include <ncurses.h>
#include <unistd.h>

#include "display_message.h"
#include "string.h"
#include "screen.h"

void display_message_center(const char *string)
{
	int max_screen_value_y, max_screen_value_x;
	int string_len;

	clear_screen();
	getmaxyx(stdscr, max_screen_value_y, max_screen_value_x);
	string_len = string_length(string);
	move(max_screen_value_y / 2, \
						(max_screen_value_x - string_len - 1) / 2);
	start_color();
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	attrset(COLOR_PAIR(4));
	addstr(string);
	refresh();
	sleep(2);
	clear_screen();
}
