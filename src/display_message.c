#include <ncurses.h>
#include <unistd.h>

#include "display_message.h"
#include "string.h"
#include "screen.h"
#include "color.h"

void
display_message_center(const char *string)
{
	int max_y, max_x;
	int string_len = string_length(string);

	getmaxyx(stdscr, max_y, max_x);

	clear_screen();

	move((max_y / 2), (max_x - string_len - 1) / 2);
	set_color(gray_on_black);
	addstr(string);

	refresh();
	sleep(2);

	clear_screen();
}

void
display_round_number(const int number)
{
	static const char *message = "Round";
	int max_y, max_x;
	int string_len = string_length(message);

	getmaxyx(stdscr, max_y, max_x);

	clear_screen();

	move(max_y / 2, (max_x - string_len - 1) / 2);
	set_color(gray_on_black);
	printw("%s %d", message, number);

	refresh();
	sleep(2);

	clear_screen();
}
