#include "screen.h"
#include "objects.h"
#include "borders.h"
#include "color.h"

#include <ncurses.h>

void
clear_screen()
{
	clear();
	refresh();
	display_borders_with_game_title();
}
