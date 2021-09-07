#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "simple_snake_game.h"

static void
clear_screen()
{
	clear();
	refresh();
}

static int
string_length(const char *string)
{
	const char *temp_string;
	temp_string = string;

	while(*temp_string)
		temp_string++;

	return (temp_string - string);
}

static int
strings_are_equal(const char *string, const char *pattern)
{
	int result = TRUE;
	if(string_length(string) == string_length(pattern)) {
		const char *temp_string = string;
		const char *temp_pattern = pattern;
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

static void
print_message(const char *string)
{
	int max_screen_value_y, max_screen_value_x;
	int string_len;

	clear_screen();
	getmaxyx(stdscr, max_screen_value_y, max_screen_value_x);
	string_len = string_length(string);
	move(max_screen_value_y / 2, (max_screen_value_x - string_len - 1) / 2);
	start_color();
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	attrset(COLOR_PAIR(4));
	addstr(string);
	refresh();
	sleep(2);
	clear_screen();
}

static void
end_program(const char *string)
{
	if(strings_are_equal(string, "request_end")) {
		print_message("request_end");
	}
	if(strings_are_equal(string, "win")) {
		print_message("win!");
	}
	if(strings_are_equal(string, "crash_end")) {
		print_message("game end!");
	}
	clear();
	endwin();
	exit(0);
}

static void 
show_object(const struct coordinate coord, const char *object_name)
{
	move(coord.y, coord.x);
	start_color();
	if(strings_are_equal(object_name, "target")) {
		init_pair(1, COLOR_WHITE, COLOR_BLACK);
		attrset(COLOR_PAIR(1));
		addch(symbol_target);
	}
	else if
	(strings_are_equal(object_name, "snake")) {
		init_pair(2, COLOR_GREEN, COLOR_BLACK);
		attrset(COLOR_PAIR(2));
		addch(symbol_snake);
	}
	else if
	(strings_are_equal(object_name, "barrier")) {
		init_pair(3, COLOR_RED, COLOR_BLACK);
		attrset(COLOR_PAIR(3));
		addch(symbol_barrier_plus);
	}
	refresh();
}

static void
hide_object(const struct coordinate coord)
{
	move(coord.y, coord.x);
	start_color();
	init_pair(4, COLOR_BLACK, COLOR_BLACK);
	attrset(COLOR_PAIR(4));
	addch(symbol_blank);
	refresh();
}

static void
print_round_number(const int number)
{
	static const char *message;
	int max_screen_value_y, max_screen_value_x;
	int string_len;

	message = "Round";
	clear_screen();
	getmaxyx(stdscr, max_screen_value_y, max_screen_value_x);
	string_len = string_length(message);
	move(max_screen_value_y / 2, (max_screen_value_x - string_len - 1) / 2);
	start_color();
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	attrset(COLOR_PAIR(4));
	printw("%s %d", message, number);
	refresh();
	sleep(2);
	clear_screen();
}

static int
get_random_coordinate(const int max_generated_num)
{
	int result;
	/*
	result = 1 + (int)(12.0 * rand() / (RAND_MAX + 1.0));	
	*/
	result = rand() % (max_generated_num + 1);
	return result;
}

static void
set_random_coordinate(struct coordinate *coord)
{
	int max_x, max_y;
	getmaxyx(stdscr, max_y, max_x);
	coord->x = get_random_coordinate(max_x);
	coord->y = get_random_coordinate(max_y);
}

static int
is_equal_coordinate(const struct coordinate coord,
					const struct coordinate pattern)
{
	int result;
	result = TRUE;

	if(coord.x != pattern.x || coord.y != pattern.y)
		result = FALSE;
	return result;
}

struct coordinate_doubly_list *
fill_in_coordinate_manual(const int max_iterator,
		const struct coordinate snake_head_coordinate)
{
	struct coordinate_doubly_list *first = NULL, *temp;
	int i;

	for(i = 0; i < max_iterator; i++) {
		temp = malloc(sizeof(struct coordinate_doubly_list));
		do {
			scanf("%d", &temp->coord.x);
			scanf("%d", &temp->coord.y);
		} while (is_equal_coordinate(temp->coord, snake_head_coordinate));

		temp->next = first;
		first = temp;
	}
	return first;
}

struct coordinate_list *
fill_in_coordinate_random(const int max_iterator,
		const struct coordinate snake_head_coordinate)
{
	struct coordinate_list *first = NULL, *temp;
	int i;

	for(i = 0; i < max_iterator; i++) {
		temp = malloc(sizeof(struct coordinate_list));
		do {
			set_random_coordinate(&temp->coord);
		} while (is_equal_coordinate(temp->coord, snake_head_coordinate));
		temp->next = first;
		first = temp;
	}
	return first;
}

static int
contact_with_borders(const struct coordinate snake_head_coordinate)
{
	int result, max_x, max_y;

	getmaxyx(stdscr, max_y, max_x);
	result = FALSE;

	if((snake_head_coordinate.x < 0) ||
		(snake_head_coordinate.x > max_x) ||
		(snake_head_coordinate.y) < 0 ||
		(snake_head_coordinate.y > max_y))
		result = TRUE;

	return result;
}
/*
static void
display_coordinate_list(const struct coordinate_list *p,
								const char *object_type)
{
	const struct coordinate_list *temp;
	for(temp = p; temp; temp = temp->next) {
		show_object(temp->coord, object_type);	
	}
}
*/
static int
contact_with_barrier(const struct coordinate snake_head_coordinate,
									struct coordinate_list *barrier)
{
	struct coordinate_list *temp;
	int result;
	result = FALSE;

	for(temp = barrier; temp; temp = temp->next) {
		if(is_equal_coordinate(snake_head_coordinate, temp->coord)) {
			result = TRUE;
			break;
		}
	}
	return result;
}

static int
contact_with_target(const struct coordinate snake_head_coordinate,
									struct coordinate_list *target)
{

	struct coordinate_list **pp;
	int result = FALSE;
	pp = &target;
	while(*pp) {
		if(is_equal_coordinate(snake_head_coordinate, (*pp)->coord)) {
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

static void
move_object(struct coordinate_deque *snake_head_coordinate,
								struct coordinate direction)
{
	struct coordinate_doubly_list *temp;
	if(direction.x == 0 && direction.y == 0) {
		for(temp = snake_head_coordinate->first; temp; temp = temp->next)
			show_object(temp->coord, "snake");
		return;
	}

	for(temp = snake_head_coordinate->first; temp; temp = temp->next)
		hide_object(temp->coord);

	for(temp = snake_head_coordinate->last; temp->prev; temp = temp->prev) {
		temp->coord.x = temp->prev->coord.x;	
		temp->coord.y = temp->prev->coord.y;	
	}
	snake_head_coordinate->first->coord.x += direction.x; 
	snake_head_coordinate->first->coord.y += direction.y; 

	for(temp = snake_head_coordinate->first; temp; temp = temp->next)
		show_object(temp->coord, "snake");	
}

static void
add_new_snake_element(struct coordinate_deque *snake_head_coordinate,
												struct coordinate c)
{
	struct coordinate_doubly_list *temp;

	temp = malloc(sizeof(struct coordinate_doubly_list));
	temp->coord.x = c.x;
	temp->coord.y = c.y;
	temp->prev = snake_head_coordinate->last;
	temp->next = NULL;
	if(snake_head_coordinate->last == NULL)
		snake_head_coordinate->first = temp;
	else
		snake_head_coordinate->last->next = temp;
	snake_head_coordinate->last = temp;
}

static void
print_object_in_fog_of_war(struct coordinate snake_head_coordinate,
										struct coordinate_list *obj,
										const char *object_type)
{
	struct coordinate_list *temp;
	int x_max, x_min, y_max, y_min;

	x_max = snake_head_coordinate.x + 5;
	x_min = snake_head_coordinate.x - 5;
	y_max = snake_head_coordinate.y + 5;
	y_min = snake_head_coordinate.y - 5;
	for(temp = obj; temp; temp = temp->next) {
		if((temp->coord.x < x_max) &&
			(temp->coord.y < y_max) &&
			(temp->coord.x > x_min) &&
			(temp->coord.y > y_min)) {
				show_object(temp->coord, object_type);
			}
	}
}

static void
set_objects_another_round(struct coordinate_deque *snake,
							struct coordinate_list **target,
							struct coordinate_list **barrier,
							const struct game_level_settings st,
							struct coordinate *coord)
{
	struct coordinate snake_head_coordinate;
	snake->first = NULL;
	snake->last = NULL;
	*barrier = NULL;
	*target = NULL;
	coord->x = 0;
	coord->y = 0;
	print_round_number(st.round_num);

	set_random_coordinate(&snake_head_coordinate);
	add_new_snake_element(snake, snake_head_coordinate);
	*barrier = fill_in_coordinate_random(st.max_barrier_amount,
										snake_head_coordinate);
	*target = fill_in_coordinate_random(max_target_amount,
									snake_head_coordinate);
}

static void
update_after_contact_with_target(struct game_level_settings *settings,
										struct coordinate_deque *snake,
										struct coordinate c)
{
	struct coordinate temp;
	temp.x = snake->last->coord.x - c.x;
	temp.y = snake->last->coord.y - c.y;

	settings->current_snake_length += 1;
	add_new_snake_element(snake, temp);
}

static void
set_settings_initial_round(struct game_level_settings *settings)
{
	settings->round_num = 1;
	settings->current_snake_length = 1;
	settings->snake_speed = 180;
	settings->max_barrier_amount = 150;
}

static void
game_settings_increase(struct game_level_settings *settings)
{
	settings->round_num += 1;
	settings->current_snake_length = 1;
	settings->snake_speed -= 20;
	settings->max_barrier_amount += 150;
}

static void
game_settings_decrease(struct game_level_settings *settings)
{
	settings->round_num -= 1;
	settings->current_snake_length = 1;
	settings->snake_speed -= 5;
	settings->max_barrier_amount -= 150;
}

static void
handle_direction_signal(int signal, struct coordinate *coord,
						struct coordinate_deque *snake)
{
	switch(signal) {
	case key_spacebar:
		coord->x = 0;
		coord->y = 0;
		break;
	case KEY_UP:
		coord->x = 0;
		coord->y = -1;
		break;
	case KEY_DOWN:
		coord->x = 0;
		coord->y = 1;
		break;
	case KEY_LEFT:
		coord->x = -1;
		coord->y = 0;
		break;
	case KEY_RIGHT:
		coord->x = 1;
		coord->y = 0;
		break;
	case ERR:
		move_object(snake, *coord);
		break;
	}
}

int
affirmative_answer_to_continue_game_request()
{
	int result, ch;
	int max_screen_value_y, max_screen_value_x;
	int string_len;
	result = FALSE;

	clear_screen();
	getmaxyx(stdscr, max_screen_value_y, max_screen_value_x);
	string_len = string_length(question_on_game_continue);

	move(max_screen_value_y / 2, (max_screen_value_x - string_len - 1) / 2);
	start_color();
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	attrset(COLOR_PAIR(4));
	addstr(question_on_game_continue);

	string_len = string_length("[y] [n]");
	move((max_screen_value_y / 2) + 2, (max_screen_value_x - string_len - 1) / 2);
	addstr("[y] [n]");
	refresh();

	while((ch = getch())) {
		switch(ch) {
			case key_yes:
				result = TRUE;
				goto quit_while_loop;
			case key_no:
				goto quit_while_loop;
			case key_escape:
				goto quit_while_loop;
		}
	}
	quit_while_loop:
	return result;
}

int main()
{
	struct coordinate_deque snake;
	struct coordinate_list *target, *barrier;
	struct coordinate coordin;
	struct game_level_settings sett;
	int direction_signal;

	srand(time(NULL));
	initscr();
	cbreak(); /* enable ctrl-c, ctrl-d */
	keypad(stdscr, 1); /* enable escape-sequences */
	noecho(); /* disable automatic input symbols on the screen */
	curs_set(0);

	print_message(greeting_message);
	set_settings_initial_round(&sett);
	timeout(sett.snake_speed);
	set_objects_another_round(&snake, &target, &barrier, sett, &coordin);

	while((direction_signal = getch()) != key_escape) {
		handle_direction_signal(direction_signal, &coordin, &snake);
		print_object_in_fog_of_war(snake.first->coord, target, "target");
		print_object_in_fog_of_war(snake.first->coord, barrier, "barrier");

		if(contact_with_borders(snake.first->coord) ||
			(contact_with_barrier(snake.first->coord, barrier))) {
			print_message("crash!");
			game_settings_decrease(&sett);
			if(sett.round_num < 1) {
				if(affirmative_answer_to_continue_game_request()) {
					set_settings_initial_round(&sett);
					set_objects_another_round(&snake,
												&target,
												&barrier,
												sett,
												&coordin);
					continue;
				} else
					end_program("crash_end");
			}
			set_objects_another_round(&snake, &target, &barrier, sett, &coordin);
		}
		if(contact_with_target(snake.first->coord, target)) {
			update_after_contact_with_target(&sett, &snake, snake.first->coord);
			if(sett.current_snake_length > max_snake_length) {
				game_settings_increase(&sett);
				if(sett.round_num > max_round_num) {
					end_program("win");
				}
				set_objects_another_round(&snake,
											&target,
											&barrier,
											sett,
											&coordin);
			}
		}
	}
	clear_screen();
	endwin();
	return 0;
}
















