#include <ncurses.h>

#include "continue_game_request.h"
#include "screen.h"
#include "string.h"
#include "color.h"

int
affirmative_answer_to_continue_game_request()
{
	int result = FALSE;
	int max_screen_value_y, max_screen_value_x;
	int string_len, answer;

	clear_screen();
	getmaxyx(stdscr, max_screen_value_y, max_screen_value_x);
	string_len = string_length(question_on_game_continue);

	move(max_screen_value_y / 2, (max_screen_value_x - string_len - 1) / 2);
	set_color(black_on_white);
	addstr(question_on_game_continue);

	string_len = string_length("[y] [n]");
	move((max_screen_value_y / 2) + 2, \
			(max_screen_value_x - string_len - 1) / 2);
	addstr("(y) (n)");
	refresh();

	while((answer = getch())) {
		switch(answer) {
			case key_yes:
				result = TRUE;
				goto quit_while_loop;
			case key_no:
				goto quit_while_loop;
			case key_escape:
				goto quit_while_loop;
		}
	}
	quit_while_loop:

	return result;
}
