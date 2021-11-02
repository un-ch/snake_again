#ifndef SNAKE_OBJECT_H_SENTRY
#define SNAKE_OBJECT_H_SENTRY

#include "coordinate.h"

void
move_snake_object(struct coordinate_deque *snake,
					struct coordinate direction);

void
add_new_snake_element(struct coordinate_deque *snake,
								struct coordinate c);

#endif
