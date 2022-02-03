#include <stddef.h>			/* for NULL */
#include <ncurses.h>		/* for getmaxyx() */
#include <borders.h>

#include "round_settings.h"
#include "coordinates.h"
#include "display_message.h"
#include "snake_object.h"
#include "target.h"

void
set_objects_another_round(struct coordinates_deque *snake,
						struct coordinates_list **target,
						struct coordinates_list **barrier,
						const struct round_settings rnd_stt,
						struct coordinates *crd)
{
	struct coordinates snake_head;

	snake->first = NULL;
	snake->last = NULL;
	*barrier = NULL;
	*target = NULL;
	crd->x = 0;
	crd->y = 0;

	display_round_number(rnd_stt.round_num);
	set_random_coordinates(&snake_head);
	add_new_snake_element(snake, snake_head);
	*barrier = fill_in_coordinates_random(rnd_stt.max_barrier_amount,
														snake_head);
	*target = fill_in_coordinates_random(max_target_amount,
												snake_head);
	display_borders_with_game_title();
}

void
set_settings_initial_round(struct round_settings *rnd_stt)
{
	int max_screen_value_x, max_screen_value_y;
	int barrier_amount;

	getmaxyx(stdscr, max_screen_value_y, max_screen_value_x);
	barrier_amount = (max_screen_value_y + max_screen_value_x) * 5;
	rnd_stt->round_num = 1;
	rnd_stt->current_snake_length = 1;
	rnd_stt->snake_speed = 180;
	rnd_stt->max_barrier_amount = barrier_amount;
}

void
game_settings_increase(struct round_settings *rnd_stt)
{
	rnd_stt->round_num += 1;
	rnd_stt->current_snake_length = 1;
	rnd_stt->snake_speed -= 20;
	rnd_stt->max_barrier_amount += 150;
}

void
game_settings_decrease(struct round_settings *rnd_stt)
{
	rnd_stt->round_num -= 1;
	rnd_stt->current_snake_length = 1;
	rnd_stt->snake_speed -= 5;
	rnd_stt->max_barrier_amount -= 150;
}

void
update_after_contact_with_target(struct round_settings *rnd_stt,
								struct coordinates_deque *snake,
										struct coordinates crd)
{
	struct coordinates temp;

	temp.x = snake->last->coord.x - crd.x;
	temp.y = snake->last->coord.y - crd.y;

	rnd_stt->current_snake_length += 1;
	add_new_snake_element(snake, temp);
}
