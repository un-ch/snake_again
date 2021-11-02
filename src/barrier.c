#include "barrier.h"
#include "coordinate.h"

int
is_contact_with_barrier(const struct coordinate c,
				const struct coordinate_list *barrier)
{
	const struct coordinate_list *temp = barrier;
	int result;
	result = FALSE;

	for(; temp; temp = temp->next) {
		if(is_equal_coordinate(c, temp->coord)) {
			result = TRUE;
			break;
		}
	}
	return result;
}
