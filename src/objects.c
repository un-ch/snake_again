#include <ncurses.h>

#include "objects.h"
#include "coordinates.h"
#include "color.h"
#include "dot_background.h"

void 
show_object_target(const struct coordinates crd)
{
	move(crd.y, crd.x);
	set_color(red_on_black);
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
	set_color(gray_on_black);
	addch(symbol_barrier);
	refresh();
}

void
show_object_dot_background(const struct coordinates crd)
{
	move(crd.y, crd.x);
	set_color(green_on_black);
	addch(symbol_dot);
	refresh();
}

void
hide_object(const struct coordinates crd)
{
	move(crd.y, crd.x);
	set_color(gray_on_black);
	addch(symbol_dot);
	refresh();
}

void
display_object(enum object obj, const struct coordinates crd)
{
	move(crd.y, crd.x);
	switch(obj) {
		case target_obj:
			set_color(green_on_black);
			addch(symbol_target);
			break;
		case snake_obj:
			set_color(red_on_black);
			addch(symbol_snake);
			break;
		case barrier_obj:
			set_color(yellow_on_black);
			addch(symbol_barrier);
			break;
		case blank_obj:
			set_color(black_on_black);
			addch(symbol_blank);
			break;
		case dot_obj:
			set_color(gray_on_black);
			addch(symbol_dot);
			break;
	}
	refresh();
}

void
display_object_in_fog_of_war(const struct coordinates sn,
				const struct coordinates_list *list,
				void (*func)(struct coordinates))
{
	const struct coordinates_list *temp = list;
	int x_max, x_min, y_max, y_min;

	x_max = sn.x + 5;
	x_min = sn.x - 5;
	y_max = sn.y + 5;
	y_min = sn.y - 5;

	while (temp) {
		if ((temp->coord.x < x_max) &&
		    (temp->coord.y < y_max) &&
		    (temp->coord.x > x_min) &&
		    (temp->coord.y > y_min)) {
			func(temp->coord);
		}

		temp = temp->next;
	}
}

void
display_in_fog_of_war(const struct coordinates sn,
			const struct coordinates_list *tar,
			const struct coordinates_list *bar,
			const struct coordinates_list *dot)
{
	/*
	* Temporary solution to resolve conflicts between targets and barriers:
	* - Display targets first.
	* - After displaying targets, barriers will overwrite them.
	*/

	display_object_in_fog_of_war(sn, tar, &show_object_target);
	display_object_in_fog_of_war(sn, bar, &show_object_barrier);
}
