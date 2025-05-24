#ifndef ROUND_SETTINGS_H
#define ROUND_SETTINGS_H

#include "coordinates.h"
#include "snake_object.h"

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
reset_settings(struct round_settings *r);

void
setup_objects(struct snake_type **s,
		struct coordinates_list **t,
		struct coordinates_list **b,
		const struct round_settings r,
		struct coordinates *c);


void
game_settings_increase(struct round_settings *r);

void
game_settings_decrease(struct round_settings *r);

void
update_after_contact_with_target(struct round_settings *r,
					struct snake_type **s,
					struct coordinates c);

#endif
