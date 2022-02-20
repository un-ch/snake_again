#include <ncurses.h>

#include "objects.h"
#include "coordinates.h"
#include "color.h"

void 
show_object_target(const struct coordinates crd)
{
	move(crd.y, crd.x);
	set_color(black_on_white);
	addch(symbol_target);
	refresh();
}

void 
show_object_snake(const struct coordinates crd)
{
	move(crd.y, crd.x);
	set_color(red_on_white);
	addch(symbol_snake);
	refresh();
}

void 
show_object_barrier(const struct coordinates crd)
{
	move(crd.y, crd.x);
	set_color(black_on_white);
	addch(symbol_barrier);
	refresh();
}

void
hide_object(const struct coordinates crd)
{
	move(crd.y, crd.x);
	set_color(black_on_white);
	addch(symbol_dot);
	refresh();
}

void
display_object(const struct coordinates crd, enum object obj)
{
	move(crd.y, crd.x);
	switch(obj) {
		case target:
			set_color(black_on_white);
			addch(symbol_target);
			break;
		case snake:
			set_color(red_on_white);
			addch(symbol_snake);
			break;
		case barrier:
			set_color(black_on_white);
			addch(symbol_barrier);
			break;
		case blank:
			set_color(black_on_white);
			addch(symbol_blank);
			break;
		case dot:
			set_color(black_on_white);
			addch(symbol_dot);
			break;
	}
	refresh();
}
