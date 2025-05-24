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
}

void 
show_object_snake(const struct coordinates crd)
{
	move(crd.y, crd.x);
	set_color(green_on_black);
	addch(symbol_snake);
}

void
show_object_barrier(const struct coordinates crd)
{
	move(crd.y, crd.x);
	set_color(gray_on_black);
	addch(symbol_barrier);
}

void
show_object_dot_background(const struct coordinates crd)
{
	move(crd.y, crd.x);
	set_color(green_on_black);
	addch(symbol_dot);
}

void
hide_object(const struct coordinates crd)
{
	move(crd.y, crd.x);
	set_color(black_on_black);
	addch(symbol_blank);
}

void
display_object(enum object obj, const struct coordinates crd)
{
	move(crd.y, crd.x);

	switch (obj) {
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
}

void
display_object_in_fog_of_war(const struct coordinates sn,
			const struct coordinates_list *list,
			void (*func)(struct coordinates))
{
	int dx, dy, dist_squared;

	const struct coordinates_list *temp = list;
	const unsigned int radius_squared = fog_radius * fog_radius;

	while (temp) {
		dx = temp->coord.x - sn.x;
		dy = temp->coord.y - sn.y;
		dist_squared = dx * dx + dy * dy;

		if (dist_squared < radius_squared) {
			func(temp->coord);
		}

		temp = temp->next;
	}
}

void
display_in_fog_of_war(const struct coordinates sn,
		const struct coordinates_list *tar,
		const struct coordinates_list *bar)
{
	/*
	* Temporary solution to resolve conflicts between targets and barriers:
	* - Display targets first.
	* - After displaying targets, barriers will overwrite them.
	*/

	display_object_in_fog_of_war(sn, tar, &show_object_target);
	display_object_in_fog_of_war(sn, bar, &show_object_barrier);
}
