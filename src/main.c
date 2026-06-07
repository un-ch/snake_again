#include <ncurses.h>
#include <stdlib.h>

#include "barrier.h"
#include "coordinates.h"
#include "end_program.h"
#include "event.h"
#include "objects.h"
#include "round_settings.h"
#include "screen.h"
#include "snake_object.h"
#include "target.h"

int
main(void)
{
	int input;
	struct event_ctx ctx = {0};

	init(&ctx);
	setup_objects(&ctx);

	while ((input = getch()) != key_escape) {
		handle_direction(input, &ctx);
		handle_event(&ctx);
	}

	release_mem(&ctx);
	end(quit);

	return exit_success;
}
