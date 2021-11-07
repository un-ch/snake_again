#include <stdlib.h>

#include "get_random_number.h"

int
get_random_int_number(const int max_generated_number)
{
	/*
	const float max_generated_number = 15.0;
	return (1 + (int)(max_generated_number* rand() / \
										(RAND_MAX + 1.0)));
	*/
	return (rand() % (max_generated_number + 1));
}
