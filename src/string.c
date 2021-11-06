
#include "string.h"

int
string_length(const char *string)
{
	const char *temp_string;
	temp_string = string;

	while(*temp_string)
		temp_string++;

	return (temp_string - string);
}

int
is_equal_strings(const char *string, const char *str_pattern)
{
	int result = TRUE;

	if(string_length(string) == string_length(str_pattern)) {
		const char *temp_string = string;
		const char *temp_pattern = str_pattern;

		while(*temp_string) {
			if(*temp_string != *temp_pattern)
				return FALSE;
			temp_string++;
			temp_pattern++;
		}
	}
	else
		result = FALSE;

	return result;
}
