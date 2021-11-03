#ifndef ROUND_SETTINGS_H_SENTRY
#define ROUND_SETTINGS_H_SENTRY

#include "coordinate.h"

struct round_settings {
	int round_num;
	int current_snake_length;
	int snake_speed;
	int max_barrier_amount;
};

void
set_objects_another_round(struct coordinate_deque *snake,
							struct coordinate_list **target,
							struct coordinate_list **barrier,
							const struct round_settings st,
							struct coordinate *coord);

void
set_settings_initial_round(struct round_settings *settings);

void
game_settings_increase(struct round_settings *settings);

void
game_settings_decrease(struct round_settings *settings);

#endif
