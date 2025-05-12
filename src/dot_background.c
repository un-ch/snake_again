#include "dot_background.h"
#include <ncurses.h>
#include <stdlib.h>
#include "color.h"
#include "screen.h"
#include "objects.h"
#include "coordinates.h"
#include "end_program.h"

void
display_dot_background(void)
{
	struct coordinates crd;
	int max_y, max_x;
	int y, x;

	getmaxyx(stdscr, max_y, max_x);
	set_color(black_on_white);

	for (y = 1; y < (max_y - 1); y++) {
		for (x = 1; x < (max_x - 1); x++) {
			crd.y = y;
			crd.x = x;
			display_object(dot_obj, crd);
		}
	}
}

void
display_dot_background_in_fog_of_war(const struct coordinates snake)
{
	int x_max, x_min, y_max, y_min;
	int y, x;
	struct coordinates c;

	x_max = snake.x + 5;
	x_min = snake.x - 5;
	y_max = snake.y + 5;
	y_min = snake.y - 5;

	y = y_min;
	x = x_min;

	for (; y < (y_max - 1); y++) {
		for (x = x_min; x < (x_max - 1); x++) {
			move(y, x);
			c.y = y;
			c.x = x;
			display_object(dot_obj, c);
			addch(symbol_dot);
		}
	}
}

struct coordinates_list *
init_dot_background(void)
{
	struct coordinates_list *first = NULL, *temp;
	int y, x;
	int max_y, max_x;

	getmaxyx(stdscr, max_y, max_x);

	for (y = 1; y < (max_y - 1); y++) {
		for (x = 1; x < (max_x - 1); x++) {
			temp = NULL;
			temp = malloc(sizeof(struct coordinates_list));

			if (!temp) {
				end(malloc_err);
			}

			temp->coord.x = x;
			temp->coord.y = y;
			temp->next = first;
			first = temp;
		}
	}

	return first;
}
