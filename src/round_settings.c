#include "round_settings.h"
#include <stddef.h>	/* for NULL */
#include <ncurses.h>	/* for getmaxyx() */
#include "borders.h"
#include "coordinates.h"
#include "display_message.h"
#include "snake_object.h"
#include "target.h"
#include "screen.h"
#include "dot_background.h"

void
reset_settings(struct round_settings *cfg)
{
	int max_x, max_y;
	int barrier_amount;

	getmaxyx(stdscr, max_y, max_x);
	barrier_amount = (max_y + max_x) * 3;
	cfg->round_num = 1;
	cfg->current_snake_length = 1;
	cfg->snake_speed = 250;
	cfg->max_barrier_amount = barrier_amount;

	apply_snake_speed(cfg->snake_speed);
}

void
setup_objects(struct coordinates_deque *snake,
		struct coordinates_list **target,
		struct coordinates_list **barrier,
		const struct round_settings cfg,
		struct coordinates *point)
{
	struct coordinates snake_head;

	if (snake->first) {
		delete_coordinate_doubly_list(&(snake->first));
	}

	if (*target) {
		delete_coordinate_list(target);
	}
	
	if (*barrier) {
		delete_coordinate_list(barrier);
	}

	snake->last = NULL;
	point->x = 0;
	point->y = 0;

	display_round_number(cfg.round_num);

	set_random_coordinates(&snake_head);
	add_new_snake_element(snake, snake_head);

	*barrier = fill_in_coordinates_random(cfg.max_barrier_amount, snake_head);
	*target = fill_in_coordinates_random(max_target_amount, snake_head);
}

void
game_settings_increase(struct round_settings *cfg)
{
	cfg->round_num += 1;
	cfg->current_snake_length = 1;
	cfg->snake_speed -= 30;
	cfg->max_barrier_amount += 150;

	apply_snake_speed(cfg->snake_speed);
}

void
game_settings_decrease(struct round_settings *cfg)
{
	cfg->round_num -= 1;
	cfg->current_snake_length = 1;
	cfg->snake_speed += 30;
	cfg->max_barrier_amount -= 150;

	apply_snake_speed(cfg->snake_speed);
}

void
update_after_contact_with_target(struct round_settings *cfg,
					struct coordinates_deque *snake,
					struct coordinates point)
{
	struct coordinates temp;

	temp.x = snake->last->coord.x - point.x;
	temp.y = snake->last->coord.y - point.y;

	cfg->current_snake_length += 1;
	add_new_snake_element(snake, temp);
}
