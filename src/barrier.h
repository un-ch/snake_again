#ifndef BARRIER_H
#define BARRIER_H

#include "coordinates.h"

int
barrier_collision(const struct coordinates head,
			const struct coordinates_list *barrier);

void
display_barrier_in_fog_of_war(const struct coordinates head,
				const struct coordinates_list *barrier);

void
display_barrier(const struct coordinates_list *barrier);

#endif
