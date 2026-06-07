#ifndef COORDINATES_H
#define COORDINATES_H

struct coordinates {
	int x;
	int y;
};

struct coordinates_list {
	struct coordinates coord;
	struct coordinates_list *next;
};

void set_random_coordinates(struct coordinates *crd);
int are_equal_coordinates(const struct coordinates *a,
				const struct coordinates *b);
struct coordinates_list *fill_in_coordinates_random(const int max_iter,
						const struct coordinates *c);
void delete_coordinate_list(struct coordinates_list **list);
void reset_direction(struct coordinates **crd);
void init_direction(struct coordinates **crd);

#endif
