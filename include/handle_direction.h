#ifndef HANDLE_DIRECTION_H_SENTRY
#define HANDLE_DIRECTION_H_SENTRY

#include "coordinate.h"

enum { key_spacebar = ' ' };

void
handle_direction_signal(int signal, struct coordinate *coord,
						struct coordinate_deque *snake);

#endif
