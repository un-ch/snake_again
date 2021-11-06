#ifndef SNAKE_OBJECT_H_SENTRY
#define SNAKE_OBJECT_H_SENTRY

#include "coordinates.h"

void
move_snake_object(struct coordinates_deque *snake,
					struct coordinates direction);

void
add_new_snake_element(struct coordinates_deque *snake,
								struct coordinates c);

#endif
