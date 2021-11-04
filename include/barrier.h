#ifndef BARRIER_H_SENTRY
#define BARRIER_H_SENTRY

#include "coordinate.h"

#define TRUE	1
#define FALSE	0

int
is_contact_with_barrier(const struct coordinate snake_head,
				const struct coordinate_list *barrier);

void
display_barrier_in_fog_of_war(struct coordinate snake_head,
							struct coordinate_list *barrier);

void
display_barrier(struct coordinate_list *barrier);

#endif
