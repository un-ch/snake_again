#ifndef SNAKE_OBJECT_H
#define SNAKE_OBJECT_H

#include "coordinates.h"

enum {
	max_snake_length = 5
};

void move_snake_object(struct coordinates_deque *s, struct coordinates d);
void add_new_snake_element(struct coordinates_deque *s, struct coordinates c);

#endif
