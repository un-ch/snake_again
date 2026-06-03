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
