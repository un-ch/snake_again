#include <ncurses.h>
#include <stdlib.h>

#include "end_program.h"
#include "display_message.h"

void
end(enum end_type how)
{
	switch(how) {
		case quit:
			display_message_center("The end.");
			break;
		case win:
			display_message_center("win!");
			break;
	}
	clear();
	endwin(); /* restore terminal after ncurses activity: */

	exit(exit_success_code);
}
