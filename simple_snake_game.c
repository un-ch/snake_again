#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

enum { symbol_target = '+' };
enum { symbol_snake = '*' };
enum { symbol_barrier_plus = 'x' };
enum { symbol_blank = ' ' };
enum { symbol_comma = ',' };
enum { symbol_parenthesis_left = '(' };
enum { symbol_parenthesis_right = ')' };
enum { key_escape = 27 };
enum { key_spacebar = ' ' };
enum { max_snake_length = 5 };
enum { max_target_amount = 4 };
enum { max_round_num = 5 };
enum { snake_speed = 120 };

static const char greeting_message[] = "Simple Snake Game";

#define TRUE 1
#define FALSE 0

struct coordinate {
	int x,y;
};

struct coordinate_double_list {
	struct coordinate coord;
	struct coordinate_double_list *next, *prev;
};

struct coordinate_deque {
	struct coordinate_double_list *first, *last;
};

struct game_level_settings {
	int round_num;
	int current_snake_length;
	int snake_speed;
	int max_barrier_amount;
};

void
clear_screen()
{
	clear();
	refresh();
}

int
string_length(const char *str)
{
	const char *temp_str;
	temp_str = str;

	while(*temp_str)
		temp_str++;

	return (temp_str - str);
}

int
strings_are_equal(const char *str_1, const char *str_2)
{
	const char *temp_str_1, *temp_str_2;
	int result = TRUE;

	if(string_length(str_1) == string_length(str_2)) {
		temp_str_1 = str_1;
		temp_str_2 = str_2;
		for(; *temp_str_1; temp_str_1++, temp_str_2++) {
			if(*temp_str_1 != *temp_str_2)
				return FALSE;
		}
	}
	else
		result = FALSE;
	return result;
}
