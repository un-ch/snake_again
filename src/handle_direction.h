#ifndef HANDLE_DIRECTION_H
#define HANDLE_DIRECTION_H

#include "coordinates.h"
#include "snake_object.h"

enum {
	key_spacebar = ' '
};

void
handle_direction(int signal, struct coordinates *crd,
			struct snake_type *snake);

#endif
