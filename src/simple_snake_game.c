
#include <time.h>		/*	for time	*/
#include <stdlib.h>		/*	for srand	*/
#include <ncurses.h>
#include <unistd.h>

#include "screen.h"
#include "string.h"

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
