#include <ncurses.h>
#include <stdlib.h>

#include "barrier.h"
#include "coordinates.h"
#include "end_program.h"
#include "event.h"
#include "handle_direction.h"
#include "round_settings.h"
#include "screen.h"
#include "snake_object.h"
#include "target.h"

int
main(void)
{
	struct snake_type *snake = NULL;
	struct coordinates_list *target = NULL, *barrier = NULL;
	struct coordinates coordinate;
	struct round_settings cfg;
	int direction;

	init_screen();
	init_snake_object(&snake);
	reset_settings(&cfg);
	setup_objects(&snake, &target, &barrier, cfg, &coordinate);

	while ((direction = getch()) != key_escape) {
		handle_direction(direction, &coordinate, snake);
		handle_event(&snake, &target, &barrier, &cfg, &coordinate);
	}

	release_mem(&snake, &target, &barrier);
	end(quit);

	return exit_success;
}
