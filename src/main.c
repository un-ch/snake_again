#include <stdlib.h>	/* for NULL */
#include <ncurses.h>	/* for getch() */
#include "end_program.h"
#include "coordinates.h"
#include "barrier.h"
#include "target.h"
#include "snake_object.h"
#include "round_settings.h"
#include "handle_direction.h"
#include "continue_game_request.h"
#include "event.h"
#include "screen.h"

int
main()
{
	struct coordinates_deque snake;
	struct coordinates_list *target = NULL, *barrier = NULL;
	struct coordinates coordinate;
	struct round_settings cfg;
	int direction;

	init_screen();
	reset_settings(&cfg);
	setup_objects(&snake, &target, &barrier, cfg, &coordinate);

	while ((direction = getch()) != key_escape) {
		handle_direction(direction, &coordinate, &snake);
		handle_event(&snake, &target, &barrier, &cfg, &coordinate);
	}

	end(quit);

	return exit_success;
}
