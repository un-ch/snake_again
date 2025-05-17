#include "dot_background.h"
#include <ncurses.h>
#include <stdlib.h>
#include "color.h"
#include "screen.h"
#include "objects.h"
#include "coordinates.h"
#include "end_program.h"

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
