#ifndef BARRIER_H_SENTRY
#define BARRIER_H_SENTRY

#include "coordinates.h"

#define TRUE	1
#define FALSE	0

int
is_contact_with_barrier(const struct coordinates snake_head,
				const struct coordinates_list *barrier);

void
display_barrier_in_fog_of_war(struct coordinates snake_head,
							struct coordinates_list *barrier);

void
display_barrier(struct coordinates_list *barrier);

#endif
