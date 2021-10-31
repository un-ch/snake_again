
#include <ncurses.h>
#include <stdlib.h>

#include "end_program.h"
#include "display_message.h"

void
end_program_request()
{
	display_message_center("request_end");
	clear();
	endwin();
	exit(0);
}

void
end_program_win()
{
	display_message_center("win!");
	clear();
	endwin();
	exit(0);
}

void
end_program_crash_end()
{
	display_message_center("game end!");
	clear();
	endwin();
	exit(0);
}
