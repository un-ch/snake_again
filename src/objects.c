#include <ncurses.h>

#include "objects.h"
#include "coordinates.h"

void 
show_object_target(const struct coordinates crd)
{
	move(crd.y, crd.x);
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	attrset(COLOR_PAIR(1));
	addch(symbol_target);
	refresh();
}

void 
show_object_snake(const struct coordinates crd)
{
	move(crd.y, crd.x);
	start_color();
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	attrset(COLOR_PAIR(2));
	addch(symbol_snake);
	refresh();
}

void 
show_object_barrier(const struct coordinates crd)
{
	move(crd.y, crd.x);
	start_color();
	init_pair(3, COLOR_RED, COLOR_BLACK);
	attrset(COLOR_PAIR(3));
	addch(symbol_barrier_plus);
	refresh();
}

void
hide_object(const struct coordinates crd)
{
	move(crd.y, crd.x);
	start_color();
	init_pair(4, COLOR_BLACK, COLOR_BLACK);
	attrset(COLOR_PAIR(4));
	addch(symbol_blank);
	refresh();
}
