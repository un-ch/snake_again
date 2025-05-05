#include <ncurses.h>
#include <stdlib.h>

#include "end_program.h"
#include "display_message.h"

void
end(enum end_type how)
{
	unsigned int status;

	switch (how) {
		case quit:
			display_message_center("The end.");
			status = exit_success_code;
			break;
		case win:
			display_message_center("Win!");
			status = exit_success_code;
			break;
		case malloc_err:
			fprintf(stderr, "Malloc error.\n");
			status = how;
	}

	clear();
	endwin(); /* restore terminal after ncurses activity: */

	exit(status);
}
