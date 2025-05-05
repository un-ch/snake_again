#ifndef ROUND_SETTINGS_H
#define ROUND_SETTINGS_H

#include "coordinates.h"

enum {
	max_round_num = 5
};

struct round_settings {
	int round_num;
	int current_snake_length;
	int snake_speed;
	int max_barrier_amount;
};

void
set_objects_another_round(struct coordinates_deque *s,
				struct coordinates_list **t,
				struct coordinates_list **b,
				struct coordinates_list **d,
				const struct round_settings r,
				struct coordinates *c);

void
set_settings_initial_round(struct round_settings *r);

void
game_settings_increase(struct round_settings *r);

void
game_settings_decrease(struct round_settings *r);

void
update_after_contact_with_target(struct round_settings *r,
					struct coordinates_deque *s,
					struct coordinates c);

#endif
