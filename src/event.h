#ifndef EVENT_H
#define EVENT_H

#include "coordinates.h"
#include "round_settings.h"

void
handle_event(struct coordinates_deque *snake,
		struct coordinates_list **tar,
		struct coordinates_list **bar,
		struct round_settings *cfg,
		struct coordinates *crd);

void
cleanup(struct coordinates_deque *snake,
		struct coordinates_list **tar,
		struct coordinates_list **bar);
#endif
