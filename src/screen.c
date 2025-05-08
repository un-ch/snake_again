#include "screen.h"
#include "objects.h"
#include "borders.h"
#include "color.h"
#include <time.h>	/* for time() */
#include <stdlib.h>	/* for srand() */

#include <ncurses.h>

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
clear_screen()
{
	clear();
	refresh();
	display_borders_with_game_title();
}
