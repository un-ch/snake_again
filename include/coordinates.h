#ifndef COORDINATES_H_SENTRY
#define COORDINATES_H_SENTRY

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
set_random_coordinates(struct coordinates *c);

int
is_equal_coordinates(const struct coordinates coord,
					const struct coordinates pattern);

struct coordinates_list *
fill_in_coordinates_random(const int max_iterator,
						const struct coordinates c);

int
is_contact_with_borders(const struct coordinates c);

#endif
