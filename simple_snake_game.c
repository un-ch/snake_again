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
string_length(const char *str)
{
	const char *temp_str;
	temp_str = str;

	while(*temp_str)
		temp_str++;

	return (temp_str - str);
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
print_message(const char *str)
{
	int max_screen_value_y, max_screen_value_x;
	int str_len;

	clear_screen();
	getmaxyx(stdscr, max_screen_value_y, max_screen_value_x);
	str_len = string_length(str);
	move(max_screen_value_y / 2, (max_screen_value_x - str_len - 1) / 2);
	start_color();
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	attrset(COLOR_PAIR(4));
	addstr(str);
	refresh();
	sleep(2);
	clear_screen();
}

static void
end_program(const char *str)
{
	if(strings_are_equal(str, "request_end")) {
		print_message("request_end");
	}
	if(strings_are_equal(str, "win")) {
		print_message("win!");
	}
	if(strings_are_equal(str, "crash_end")) {
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
print_round_number(const int num)
{
	static const char *msg;
	int max_screen_value_y, max_screen_value_x;
	int str_len;

	msg = "Round";
	clear_screen();
	getmaxyx(stdscr, max_screen_value_y, max_screen_value_x);
	str_len = string_length(msg);
	move(max_screen_value_y / 2, (max_screen_value_x - str_len - 1) / 2);
	start_color();
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	attrset(COLOR_PAIR(4));
	printw("%s %d", msg, num);
	refresh();
	sleep(2);
	clear_screen();
}

static int
get_random_coordinate(int max_generated_num)
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
is_equal_coordinate(const struct coordinate c, const struct coordinate d)
{
	int result;
	result = TRUE;

	if(c.x != d.x || c.y != d.y)
		result = FALSE;
	return result;
}

struct coordinate_doubly_list *
fill_in_coordinate_manual(const int max_iterator, const struct coordinate snk)
{
	struct coordinate_doubly_list *first = NULL, *temp;
	int i;

	for(i = 0; i < max_iterator; i++) {
		temp = malloc(sizeof(struct coordinate_doubly_list));
		do {
			scanf("%d", &temp->coord.x);
			scanf("%d", &temp->coord.y);
		} while (is_equal_coordinate(temp->coord, snk));

		temp->next = first;
		first = temp;
	}
	return first;
}

struct coordinate_list *
fill_in_coordinate_random(const int max_iterator,
							const struct coordinate snk)
{
	struct coordinate_list *first = NULL, *temp;
	int i;

	for(i = 0; i < max_iterator; i++) {
		temp = malloc(sizeof(struct coordinate_list));
		do {
			set_random_coordinate(&temp->coord);
		} while (is_equal_coordinate(temp->coord, snk));
		temp->next = first;
		first = temp;
	}
	return first;
}

/*
static void
print_list_value(const struct coordinate_doubly_list*p)
{
	const struct coordinate_doubly_list *temp;
	for(temp = p; temp; temp = temp->next) {
		printf("%d, %d\n", temp->coord.x, temp->coord.y);
		sleep(1);
	}
}
*/

static int
contact_with_borders(const struct coordinate snk_head)
{
	int result, max_x, max_y;

	getmaxyx(stdscr, max_y, max_x);
	result = FALSE;

	if((snk_head.x < 0) ||
		(snk_head.x > max_x) ||
		(snk_head.y) < 0 ||
		(snk_head.y > max_y))
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
contact_with_barrier(const struct coordinate snk_head,
						struct coordinate_list *brr)
{
	struct coordinate_list *temp;
	int result;
	result = FALSE;

	for(temp = brr; temp; temp = temp->next) {
		if(is_equal_coordinate(snk_head, temp->coord)) {
			result = TRUE;
			break;
		}
	}
	return result;
}

static int
contact_with_target(const struct coordinate snk_head,
						struct coordinate_list *trg)
{

	struct coordinate_list **pp;
	int result;
	result = FALSE;
	pp = &trg;
	while(*pp) {
		if(is_equal_coordinate(snk_head, (*pp)->coord)) {
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
move_object(struct coordinate_deque *snk, struct coordinate direction)
{
	struct coordinate_doubly_list *temp;

	for(temp = snk->first; temp; temp = temp->next)
		hide_object(temp->coord);

	for(temp = snk->last; temp->prev; temp = temp->prev) {
		temp->coord.x = temp->prev->coord.x;	
		temp->coord.y = temp->prev->coord.y;	
	}
	snk->first->coord.x += direction.x; 
	snk->first->coord.y += direction.y; 

	for(temp = snk->first; temp; temp = temp->next)
		show_object(temp->coord, "snake");	
}

static void
add_new_snake_element(struct coordinate_deque *snk, struct coordinate c)
{
	struct coordinate_doubly_list *temp;

	temp = malloc(sizeof(struct coordinate_doubly_list));
	temp->coord.x = c.x;
	temp->coord.y = c.y;
	temp->prev = snk->last;
	temp->next = NULL;
	if(snk->last == NULL)
		snk->first = temp;
	else
		snk->last->next = temp;
	snk->last = temp;
}

static void
print_object_in_fog_of_war(struct coordinate snk_head,
							struct coordinate_list *obj,
							const char *object_type)
{
	struct coordinate_list *temp_obj;
	int x_max, x_min, y_max, y_min;

	x_max = snk_head.x + 5;
	x_min = snk_head.x - 5;
	y_max = snk_head.y + 5;
	y_min = snk_head.y - 5;
	for(temp_obj = obj; temp_obj; temp_obj = temp_obj->next) {
		if((temp_obj->coord.x < x_max) &&
			(temp_obj->coord.y < y_max) &&
			(temp_obj->coord.x > x_min) &&
			(temp_obj->coord.y > y_min)) {
				show_object(temp_obj->coord, object_type);
			}
	}
}

static void
set_objects_another_round(struct coordinate_deque *snk,
							struct coordinate_list **trg,
							struct coordinate_list **brr,
							const struct game_level_settings st,
							struct coordinate *coord)
{
	struct coordinate snk_head;
	snk->first = NULL;
	snk->last = NULL;
	*brr = NULL;
	*trg = NULL;
	coord->x = 0;
	coord->y = 0;
	print_round_number(st.round_num);

	set_random_coordinate(&snk_head);
	add_new_snake_element(snk, snk_head);
	*brr = fill_in_coordinate_random(st.max_barrier_amount, snk_head);
	*trg = fill_in_coordinate_random(max_target_amount, snk_head);
}

static void
update_after_contact_with_target(struct game_level_settings *st,
									struct coordinate_deque *snk,
									struct coordinate c)
{
	struct coordinate temp;
	temp.x = snk->last->coord.x - c.x;
	temp.y = snk->last->coord.y - c.y;

	st->current_snake_length += 1;
	add_new_snake_element(snk, temp);
}

static void
set_settings_initial_round(struct game_level_settings *st)
{
	st->round_num = 1;
	st->current_snake_length = 1;
	st->snake_speed = 180;
	st->max_barrier_amount = 150;
}

static void
game_settings_increase(struct game_level_settings *st)
{
	st->round_num += 1;
	st->current_snake_length = 1;
	st->snake_speed -= 20;
	st->max_barrier_amount += 150;
}

static void
game_settings_decrease(struct game_level_settings *st)
{
	st->round_num -= 1;
	st->current_snake_length = 1;
	st->snake_speed -= 5;
	st->max_barrier_amount -= 150;
}

static void
handle_direction_signal(int signal, struct coordinate *c,
						struct coordinate_deque *snk)
{
	switch(signal) {
	case key_spacebar:
		c->x = 0;
		c->y = 0;
		break;
	case KEY_UP:
		c->x = 0;
		c->y = -1;
		break;
	case KEY_DOWN:
		c->x = 0;
		c->y = 1;
		break;
	case KEY_LEFT:
		c->x = -1;
		c->y = 0;
		break;
	case KEY_RIGHT:
		c->x = 1;
		c->y = 0;
		break;
	case ERR:
		move_object(snk, *c);
		break;
	}
}

int
affirmative_answer_to_continue_game_request()
{
	int result, ch;
	int max_screen_value_y, max_screen_value_x;
	int str_len;
	result = FALSE;

	clear_screen();
	getmaxyx(stdscr, max_screen_value_y, max_screen_value_x);
	str_len = string_length(question_on_game_continue);

	move(max_screen_value_y / 2, (max_screen_value_x - str_len - 1) / 2);
	start_color();
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	attrset(COLOR_PAIR(4));
	addstr(question_on_game_continue);

	str_len = string_length("[y] [n]");
	move((max_screen_value_y / 2) + 2, (max_screen_value_x - str_len - 1) / 2);
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
					set_objects_another_round(&snake, &target, &barrier, sett, &coordin);
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
				set_objects_another_round(&snake, &target, &barrier, sett, &coordin);
			}
		}
	}
	clear_screen();
	endwin();
	return 0;
}
















