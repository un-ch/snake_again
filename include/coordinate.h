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

void
set_random_coordinate(struct coordinate *coord);

int
is_equal_coordinate(const struct coordinate coord,
					const struct coordinate pattern);

struct coordinate_list *
fill_in_coordinate_random(const int max_iterator,
						const struct coordinate snake_head_coordinate);

int
contact_with_borders(const struct coordinate snake_head_coordinate);

#endif
