#include <ncurses.h>
#include <stdlib.h>

#include "end_program.h"
#include "display_message.h"

void
end(enum end_type how)
{
	unsigned int status = exit_success;

	switch (how) {
	case quit:
		display_message_center("The end.");
		break;
	case win:
		display_message_center("Win!");
		break;
	case malloc_err:
		/* TODO: correct error handling */
		fprintf(stderr, "Malloc error.\n");
		status = how;
		break;
	case monochrome_display:
		/* TODO: correct error handling */
		fprintf(stderr, "Monochrome display: black and white colors only.\n");
		status = how;
		break;
	default:
		break;
	}

	clear();
	endwin(); /* restore terminal after ncurses activity */

	exit(status);
}
