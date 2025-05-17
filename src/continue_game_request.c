#include <ncurses.h>
#include "continue_game_request.h"
#include "screen.h"
#include "string.h"
#include "color.h"

bool
affirmative_answer_to_continue_game_request(void)
{
	bool result = false;
	int max_y, max_x;
	int string_len, answer;

	clear_screen();
	getmaxyx(stdscr, max_y, max_x);
	string_len = string_length(continue_question);

	move(max_y / 2, (max_x - string_len - 1) / 2);
	set_color(gray_on_black);
	addstr(continue_question);

	string_len = string_length("(y) (n)");

	move((max_y / 2) + 2, (max_x - string_len - 1) / 2);
	addstr("(y) (n)");

	while ((answer = getch())) {
		switch (answer) {
		case key_yes:
			return true;
		case key_no:
			return false;
		case key_escape:
			return false;
		}
	}

	return result;
}
