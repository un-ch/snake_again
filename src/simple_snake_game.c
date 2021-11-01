
#include <time.h>		/*	for time	*/
#include <stdlib.h>		/*	for srand	*/
#include <ncurses.h>

#include "screen.h"
#include "string.h"
#include "display_message.h"
#include "end_program.h"
#include "objects.h"
#include "get_random_number.h"
#include "coordinate.h"

enum {exit_success_code = 0 };

int main()
{
	srand(time(NULL));
	initscr();
	/* enable ctrl-c, ctrl-d: */
	cbreak();
	/* enable escape-sequences: */
	keypad(stdscr, 1);
	/* disable automatic input symbols on the screen: */
	noecho();
	curs_set(0);


	/* restore terminal after ncurses activity: */
	endwin();

	return exit_success_code;
}
