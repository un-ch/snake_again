#include <ncurses.h>
#include <time.h>	/* for time() */
#include <stdlib.h>	/* for srand() */

#include "screen.h"
#include "objects.h"
#include "borders.h"
#include "color.h"

void
init_screen(void)
{
	srand(time(NULL));
	initscr();
	start_color();
	/* enable ctrl-c, ctrl-d: */
	cbreak();
	/* enable escape-sequences: */
	keypad(stdscr, 1);
	/* disable automatic input symbols on the screen: */
	noecho();
	curs_set(0);
}

void
clear_screen(void)
{
	clear();
	display_borders_with_game_title();
}
