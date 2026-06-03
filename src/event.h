#ifndef EVENT_H
#define EVENT_H

#include "coordinates.h"
#include "round_settings.h"

enum {
	key_escape = 27,
	key_yes = 121,
	key_no = 110
};

void handle_event(struct snake_type **snake,
		struct coordinates_list **tar,
		struct coordinates_list **bar,
		struct round_settings *cfg,
		struct coordinates *crd);

int resuming(void);

void cleanup(struct snake_type **snake,
		struct coordinates_list **tar,
		struct coordinates_list **bar);

void release_mem(struct snake_type **snake,
		struct coordinates_list **tar,
		struct coordinates_list **bar);

#endif
