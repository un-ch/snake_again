#include <ncurses.h>

#include "end_program.h"
#include "event.h"

int
main(void)
{
	int input;
	struct event_ctx ctx = {0};

	init(&ctx);

	while ((input = getch()) != key_escape) {
		handle_direction(input, &ctx);
		handle_event(&ctx);
	}

	release_mem(&ctx);
	end(quit);

	return exit_success;
}
