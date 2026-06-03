#include <ncurses.h>

#include "continue_game_request.h"
#include "color.h"
#include "screen.h"
#include "string.h"

static int
get_user_input(void)
{
	int answer;

	while (answer = getch()) {
		switch (answer) {
		case key_yes:
			return 1;
		case key_no:
		case key_escape:
			return 0;
		default:
			break;
		}
	}
}

int
continue_game_confirmed(void)
{
	const char quest[] = "Crash! Would you like to continue the game?";
	int max_y, max_x, rc, len;

	getmaxyx(stdscr, max_y, max_x);
	len = string_length(quest);

	clear_screen();
	move(max_y / 2, (max_x - len - 1) / 2);
	set_color(gray_on_black);
	addstr(quest);

	len = string_length("(y) (n)");

	move((max_y / 2) + 2, (max_x - len - 1) / 2);
	addstr("(y) (n)");

	rc = get_user_input();

	return rc;
}
