#ifndef COORDINATE_H_SENTRY
#define COORDINATE_H_SENTRY

struct coordinate {
	int x;
	int y;
};

void
set_random_coordinate(struct coordinate *coord);

int
is_equal_coordinate(const struct coordinate coord,
					const struct coordinate pattern);

#endif
