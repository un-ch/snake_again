#include <stdbool.h>

#include "string.h"

int
string_length(const char *str)
{
	const char *temp = str;

	while (*temp) {
		temp++;
	}

	return (temp - str);
}

bool
is_equal_strings(const char *a, const char *b)
{
	int result = true;

	if (string_length(a) == string_length(b)) {
		const char *temp_a = a;
		const char *temp_b = b;

		while (*temp_a) {
			if (*temp_a != *temp_b) {
				return false;
			}

			temp_a++;
			temp_b++;
		}

	} else
		result = false;

	return result;
}
