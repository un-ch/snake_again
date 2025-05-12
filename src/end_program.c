#include "end_program.h"
#include <ncurses.h>
#include <stdlib.h>
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
		fprintf(stderr, "Malloc error.\n");
		status = how;
		break;
	case monochrome_display:
		fprintf(stderr, "Monochrome display: just black and white colors.\n");
		status = how;
		break;
	default:
		break;
	}

	clear();
	endwin(); /* restore terminal after ncurses activity: */

	exit(status);
}
