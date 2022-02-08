#include <ncurses.h>
#include <stdlib.h>

#include "end_program.h"
#include "display_message.h"

void
end(int end_type)
{
	switch(end_type) {
		case quit:
			display_message_center("end!");
			break;
		case win:
			display_message_center("win!");
			break;
	}
	clear();
	endwin();
	exit(0);
}
