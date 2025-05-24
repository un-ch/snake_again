#ifndef SNAKE_OBJECT_H
#define SNAKE_OBJECT_H

#include "coordinates.h"

enum {
	max_snake_length = 15
};

struct snake_type {
	struct coordinates_list *first;
	struct coordinates_list *last;
	struct coordinates *last_direction;
};

void
init_snake_object(struct snake_type **s);

void
move_snake_object(struct snake_type *s, struct coordinates d);

void
add_new_snake_element(struct snake_type **s, struct coordinates c);

void
apply_snake_speed(const unsigned int speed);

void
display_object_list(const struct coordinates_list *list, void (*func)(struct coordinates c));

#endif
