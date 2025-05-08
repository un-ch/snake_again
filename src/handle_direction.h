#ifndef HANDLE_DIRECTION_H
#define HANDLE_DIRECTION_H

#include "coordinates.h"

enum { key_spacebar = ' ' };

void
handle_direction(int signal, struct coordinates *crd,
			struct coordinates_deque *snake);

#endif
