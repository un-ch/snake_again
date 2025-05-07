#include <time.h>	/* for time() */
#include <stdlib.h>	/* for srand() */
#include <ncurses.h>
#include "end_program.h"
#include "coordinates.h"
#include "barrier.h"
#include "target.h"
#include "snake_object.h"
#include "round_settings.h"
#include "handle_direction.h"
#include "continue_game_request.h"
#include "event.h"

int main()
{
	srand(time(NULL));
	initscr();
	start_color();
	/* enable ctrl-c, ctrl-d: */
	cbreak();
	/* enable escape-sequences: */
	keypad(stdscr, 1);
	/* disable automatic input symbols on the screen: */
	noecho();
	curs_set(0);

	struct coordinates_deque snake;
	struct coordinates_list *target = NULL, *barrier = NULL;
	struct coordinates coordinate;
	struct round_settings cfg;
	int direction_signal;

	set_settings_initial_round(&cfg);

	set_objects_another_round(&snake, &target, &barrier, cfg, &coordinate);

	while ((direction_signal = getch()) != key_escape) {
		handle_direction_signal(direction_signal, &coordinate, &snake);
		handle_event(&snake, &target, &barrier, &cfg, &coordinate);
	}

	end(quit);

	return exit_success_code;
}
