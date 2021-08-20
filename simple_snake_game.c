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
	sleep(1);
	clear_screen();
}

static void
end_program(const char *str)
{
	if(strings_are_equal(str, "request_end"))
		print_message("request_end");	

	if(strings_are_equal(str, "crash_end"))
		print_message("bye!");

	if(strings_are_equal(str, "win"))
		print_message("win!");

/*
	
	if(str == "request_end") {
			
	}
	if(str == "crash_end") {
		print_message("bye!");
	}
	if(str == "win_end") {
		print_message("win!");
	}
	*/
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
	msg = "Round";
	print_message(msg);
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
fill_in_coordinate_random(const int max_iterator,
							const struct coordinate snk)
{
	struct coordinate_doubly_list *first = NULL, *temp;
	int i;

	for(i = 0; i < max_iterator; i++) {
		temp = malloc(sizeof(struct coordinate_doubly_list));
		do {
			set_random_coordinate(&temp->coord);
		} while (is_equal_coordinate(temp->coord, snk));
		temp->next = first;
		first = temp;
	}
	return first;
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

static void
print_list_value(const struct coordinate_doubly_list*p)
{
	const struct coordinate_doubly_list *temp;
	for(temp = p; temp; temp = temp->next) {
		printf("%d, %d\n", temp->coord.x, temp->coord.y);
		sleep(1);
	}
}

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

static void
show_coordinate_doubly_list(const struct coordinate_doubly_list *p,
								const char *object_type)
{
	const struct coordinate_doubly_list *temp;
	for(temp = p; temp; temp = temp->next) {
		show_object(temp->coord, object_type);	
	}
}

static int
contact_with_barrier(const struct coordinate snk_head,
						struct coordinate_doubly_list *brr)
{
	struct coordinate_doubly_list *temp;
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
						struct coordinate_deque *trg)
{
	struct coordinate_doubly_list *temp;
	int result;
	result = FALSE;
	for(temp = trg->first; temp; temp = temp->next) {
		if(is_equal_coordinate(snk_head, temp->coord)) {
			/*
			if(temp->prev)
				temp->prev->next = temp->next;
			else
				trg->first = temp->next;
			if(temp->next)
				temp->next->prev = temp->prev;
			else
				trg->last = temp->prev;
			free(temp);
			*/
			temp->coord.x = 0;
			temp->coord.y = 0;
			result = TRUE;
			break;
		}
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

/*
static void
print_object_in_fog_of_war(struct coordinate snk_head,
							struct coordinate_doubly_list *obj,
							const char *object_type)
{
	struct coordinate_doubly_list *temp_obj;
	int x_max, x_min, y_max, y_min;

	x_max = snk_head.x + 5;
	x_min = snk_head.x - 5;
	y_max = snk_head.y + 5;
	y_max = snk_head.y - 5;
	for(temp_obj = obj; temp_obj; temp_obj = temp_obj->next) {
		
	}

}
*/


static void
set_objects_another_round(struct coordinate_deque *snk,
							struct coordinate_deque *trg,
							struct coordinate_deque *brr,
							struct game_level_settings st)
{
	struct coordinate snk_head;
	snk->first = NULL;
	snk->last = NULL;
	trg->first = NULL;
	trg->last = NULL;
	brr->first = NULL;
	brr->last = NULL;

	set_random_coordinate(&snk_head);
	add_new_snake_element(snk, snk_head);

	trg->first = fill_in_coordinate_random(max_target_amount, snk_head);
	brr->first = fill_in_coordinate_random(st.max_barrier_amount, snk_head);
	show_coordinate_doubly_list(trg->first, "target");
	show_coordinate_doubly_list(brr->first, "barrier");
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
	st->snake_speed = 100;
	st->max_barrier_amount = 150;
}

static void
game_settings_increase(struct game_level_settings *st)
{
	st->round_num += 1;
	st->current_snake_length = 1;
	st->snake_speed -= 1;
	st->max_barrier_amount += 10;
}

static void
game_settings_decrease(struct game_level_settings *st)
{
	st->round_num -= 1;
	st->current_snake_length = 1;
	st->snake_speed -= 1;
	st->max_barrier_amount -= 10;
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
/*
int
affirmative_answer_to_continue_game_request()
{
	int result, ch;
	result = FALSE;
	int max_screen_value_y, max_screen_value_x;
	int str_len;

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
	while((ch = getch()) != key_escape ||
			(ch = getch()) != key_yes ||
			(ch = getch()) != key_no)
		{}
	if(ch == key_yes)
		result = TRUE;

	return result;
}
*/

int main()
{
	struct coordinate_deque snake, target, barrier;
	struct coordinate coordin;
	struct game_level_settings sett;
	int direction_signal;

	srand(time(NULL));
	initscr();
	cbreak();
	keypad(stdscr, 1);
	noecho();
	curs_set(0);
	clear_screen();

	print_message(greeting_message);
	set_settings_initial_round(&sett);
	timeout(sett.snake_speed);
	coordin.x = 0;
	coordin.y = 0;

	set_objects_another_round(&snake, &target, &barrier, sett);

	while((direction_signal = getch()) != key_escape) {
		handle_direction_signal(direction_signal, &coordin, &snake);

		if(contact_with_borders(snake.first->coord) ||
			(contact_with_barrier(snake.first->coord, barrier.first))) {
			/*game_settings_decrease(&sett);*/
			print_message("crash");
			end_program("crash_end");
		}
		if(contact_with_target(snake.first->coord, &target)) {
			update_after_contact_with_target(&sett, &snake, snake.first->coord);
			if(sett.current_snake_length > max_snake_length) {
				end_program("win");
			}
		}
		/*

			if(sett.round_num < 1) {

				if(affirmative_answer_to_continue_game_request) {
					set_settings_initial_round(&sett);
					direction_signal = key_spacebar;
				}
				else
					end_program("crash_end");

			}
			set_objects_another_round
		}
		*/
	}
	
	clear_screen();
	endwin();

	return 0;
}
















