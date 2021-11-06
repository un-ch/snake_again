#include <ncurses.h>
#include "handle_direction.h"
#include "snake_object.h"
#include "coordinates.h"

void
handle_direction_signal(int signal, struct coordinates *coord,
						struct coordinates_deque *snake)
{
	switch(signal) {
	case key_spacebar:
		coord->x = 0;
		coord->y = 0;
		break;
	case KEY_UP:
		coord->x = 0;
		coord->y = -1;
		break;
	case KEY_DOWN:
		coord->x = 0;
		coord->y = 1;
		break;
	case KEY_LEFT:
		coord->x = -1;
		coord->y = 0;
		break;
	case KEY_RIGHT:
		coord->x = 1;
		coord->y = 0;
		break;
	case ERR:
		move_snake_object(snake, *coord);
		break;
	}
}

