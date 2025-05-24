#include <stdlib.h>

#include "get_random_number.h"

int
get_random_int_number(const int min_generated_number,
			const int max_generated_number)
{
	int result;

	result = (min_generated_number + (int) \
		((float)(max_generated_number) * rand() / (RAND_MAX + 1.0)));

	return result;
}
