#include <stddef.h>		/* for NULL */
#include <ncurses.h>		/* for getmaxyx() */
#include "borders.h"
#include "round_settings.h"
#include "coordinates.h"
#include "display_message.h"
#include "snake_object.h"
#include "target.h"
#include "screen.h"
#include "dot_background.h"

void
set_objects_another_round(struct coordinates_deque *snake,
				struct coordinates_list **target,
				struct coordinates_list **barrier,
				struct coordinates_list **dot_back,
				const struct round_settings st,
				struct coordinates *point)
{
	struct coordinates snake_head;

	if (*target) {
		delete_coordinate_list(target);
		delete_coordinate_list(barrier);
		delete_coordinate_list(dot_back);
		delete_coordinate_doubly_list(&(snake->first));
	}

	snake->first = NULL;
	snake->last = NULL;
	*barrier = NULL;
	*target = NULL;
	*dot_back = NULL;
	point->x = 0;
	point->y = 0;

	display_round_number(st.round_num);

	set_random_coordinates(&snake_head);
	add_new_snake_element(snake, snake_head);
	*barrier = fill_in_coordinates_random(st.max_barrier_amount, snake_head);
	*target = fill_in_coordinates_random(max_target_amount, snake_head);
}

void
set_settings_initial_round(struct round_settings *st)
{
	int max_x, max_y;
	int barrier_amount;

	getmaxyx(stdscr, max_y, max_x);
	barrier_amount = (max_y + max_x) * 5;
	st->round_num = 1;
	st->current_snake_length = 1;
	st->snake_speed = 250;
	st->max_barrier_amount = barrier_amount;
}

void
game_settings_increase(struct round_settings *st)
{
	st->round_num += 1;
	st->current_snake_length = 1;
	st->snake_speed -= 50;
	st->max_barrier_amount += 150;
}

void
game_settings_decrease(struct round_settings *st)
{
	st->round_num -= 1;
	st->current_snake_length = 1;
	st->snake_speed -= 5;
	st->max_barrier_amount -= 150;
}

void
update_after_contact_with_target(struct round_settings *st,
				struct coordinates_deque *snake,
					struct coordinates point)
{
	struct coordinates temp;

	temp.x = snake->last->coord.x - point.x;
	temp.y = snake->last->coord.y - point.y;

	st->current_snake_length += 1;
	add_new_snake_element(snake, temp);
}
