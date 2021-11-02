#ifndef COORDINATE_H_SENTRY
#define COORDINATE_H_SENTRY

struct coordinate {
	int x;
	int y;
};

struct coordinate_list {
	struct coordinate coord;
	struct coordinate_list *next;
};

struct coordinate_doubly_list {
	struct coordinate coord;
	struct coordinate_doubly_list *next, *prev;
};

struct coordinate_deque {
	struct coordinate_doubly_list *first, *last;
};

void
set_random_coordinate(struct coordinate *c);

int
is_equal_coordinate(const struct coordinate coord,
					const struct coordinate pattern);

struct coordinate_list *
fill_in_coordinate_random(const int max_iterator,
						const struct coordinate c);

int
is_contact_with_borders(const struct coordinate c);

#endif
