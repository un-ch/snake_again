#include	<ncurses.h>

#include	"screen.h"

void
clear_screen()
{
	clear();
	refresh();
}
