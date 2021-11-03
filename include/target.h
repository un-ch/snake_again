#ifndef TARGET_H_SENTRY
#define TARGET_H_SENTRY

#include "coordinate.h"

#define TRUE	1
#define FALSE	0

enum { max_target_amount = 20 };

int
is_contact_with_target(const struct coordinate c,
					struct coordinate_list *target);

void
display_target_in_fog_of_war(struct coordinate snake,
							struct coordinate_list *tar);

#endif
