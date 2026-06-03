#ifndef BARRIER_H
#define BARRIER_H

#include "coordinates.h"

int
is_contact_with_barrier(const struct coordinates head,
			const struct coordinates_list *barrier);

void
display_barrier_in_fog_of_war(const struct coordinates head,
				const struct coordinates_list *barrier);

void
display_barrier(const struct coordinates_list *barrier);

#endif
