#ifndef TARGET_H
#define TARGET_H

#include <stdbool.h>

#include "coordinates.h"

enum {
	max_target_amount = 100
};

bool
is_contact_with_target(const struct coordinates crd,
			struct coordinates_list *target);

void
display_target_in_fog_of_war(struct coordinates snake,
			struct coordinates_list *target);

void
display_target(struct coordinates_list *target);

#endif
