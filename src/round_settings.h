#ifndef ROUND_SETTINGS_H
#define ROUND_SETTINGS_H

#include "coordinates.h"

enum {
	max_rounds = 5
};

struct round_settings {
	int round;
	int current_snake_length;
	int snake_speed;
	int max_barriers;
};

void init_round_settings(struct round_settings **cfg);
void reset_settings(struct round_settings **cfg);
void game_settings_increase(struct round_settings *cfg);
void game_settings_decrease(struct round_settings *cfg);

#endif
