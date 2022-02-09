#include <ncurses.h>

#include "objects.h"
#include "coordinates.h"
#include "color.h"

void 
show_object_target(const struct coordinates crd)
{
	move(crd.y, crd.x);
	set_color(white_on_black);
	addch(symbol_target);
	refresh();
}

void 
show_object_snake(const struct coordinates crd)
{
	move(crd.y, crd.x);
	set_color(green_on_black);
	addch(symbol_snake);
	refresh();
}

void 
show_object_barrier(const struct coordinates crd)
{
	move(crd.y, crd.x);
	set_color(red_on_black);
	addch(symbol_barrier);
	refresh();
}

void
hide_object(const struct coordinates crd)
{
	move(crd.y, crd.x);
	set_color(black_on_black);
	addch(symbol_blank);
	refresh();
}
