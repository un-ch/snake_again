#ifndef HANDLE_DIRECTION_H_SENTRY
#define HANDLE_DIRECTION_H_SENTRY

#include "coordinates.h"

enum { key_spacebar = ' ' };

void
handle_direction_signal(int signal, struct coordinates *crd,
							struct coordinates_deque *snake);

#endif
