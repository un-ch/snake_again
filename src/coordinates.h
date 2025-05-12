#ifndef COORDINATES_H
#define COORDINATES_H

#include <stdbool.h>

struct coordinates {
	int x;
	int y;
};

struct coordinates_list {
	struct coordinates coord;
	struct coordinates_list *next;
};

struct coordinates_doubly_list {
	struct coordinates coord;
	struct coordinates_doubly_list *next, *prev;
};

struct coordinates_deque {
	struct coordinates_doubly_list *first, *last;
};

void
set_random_coordinates(struct coordinates *crd);

bool
is_equal_coordinates(const struct coordinates a, const struct coordinates b);

struct coordinates_list *
fill_in_coordinates_random(const int max_iter, const struct coordinates c);

void
delete_coordinate_list(struct coordinates_list **list);

void
delete_coordinate_doubly_list(struct coordinates_doubly_list **list);

#endif
