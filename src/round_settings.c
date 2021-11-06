#include <stddef.h>			/* for NULL */
#include "round_settings.h"
#include "coordinates.h"
#include "display_message.h"
#include "snake_object.h"
#include "target.h"

void
set_objects_another_round(struct coordinates_deque *snake,
							struct coordinates_list **target,
							struct coordinates_list **barrier,
							const struct round_settings st,
							struct coordinates *coord)
{
	struct coordinates snake_head_coordinate;

	snake->first = NULL;
	snake->last = NULL;
	*barrier = NULL;
	*target = NULL;
	coord->x = 0;
	coord->y = 0;
	display_round_number(st.round_num);
	set_random_coordinates(&snake_head_coordinate);
	add_new_snake_element(snake, snake_head_coordinate);
	*barrier = fill_in_coordinates_random(st.max_barrier_amount,
										snake_head_coordinate);
	*target = fill_in_coordinates_random(max_target_amount,
									snake_head_coordinate);
}

void
set_objects_another_round(struct coordinates_deque *snake,
							struct coordinates_list **target,
							struct coordinates_list **barrier,
							const struct round_settings st,
							struct coordinates *coord);

void
set_settings_initial_round(struct round_settings *settings)
{
	settings->round_num = 1;
	settings->current_snake_length = 1;
	settings->snake_speed = 180;
	settings->max_barrier_amount = 150;
}

void
game_settings_increase(struct round_settings *settings)
{
	settings->round_num += 1;
	settings->current_snake_length = 1;
	settings->snake_speed -= 20;
	settings->max_barrier_amount += 150;
}

void
game_settings_decrease(struct round_settings *settings)
{
	settings->round_num -= 1;
	settings->current_snake_length = 1;
	settings->snake_speed -= 5;
	settings->max_barrier_amount -= 150;
}

void
update_after_contact_with_target(struct round_settings *settings,
										struct coordinates_deque *snake,
										struct coordinates c)
{
	struct coordinates temp;
	temp.x = snake->last->coord.x - c.x;
	temp.y = snake->last->coord.y - c.y;

	settings->current_snake_length += 1;
	add_new_snake_element(snake, temp);
}
