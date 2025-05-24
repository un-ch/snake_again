#ifndef BARRIER_H
#define BARRIER_H

#include <stdbool.h>

#include "coordinates.h"

bool
is_contact_with_barrier(const struct coordinates snake_head,
			const struct coordinates_list *barrier);

void
display_barrier_in_fog_of_war(const struct coordinates snake_head,
				const struct coordinates_list *barrier);

void
display_barrier(const struct coordinates_list *barrier);

#endif
