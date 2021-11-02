#include <stdlib.h>		/* for free() */

#include "target.h"
#include "coordinate.h"

int
is_contact_with_target(const struct coordinate c,
					struct coordinate_list *target)
{
	struct coordinate_list **pp = &target;
	int result = FALSE;

	while(*pp) {
		if(is_equal_coordinate(c, (*pp)->coord)) {
			struct coordinate_list *temp = *pp;
			*pp = (*pp)->next;
			free(temp);
			result = TRUE;
			break;
		}
		pp = &(*pp)->next;
	}
	return result;
}
