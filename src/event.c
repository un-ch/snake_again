#include "event.h"
#include <stddef.h>
#include <stdlib.h>
#include "coordinates.h"
#include "handle_direction.h"
#include "objects.h"
#include "borders.h"
#include "round_settings.h"
#include "end_program.h"
#include "barrier.h"
#include "continue_game_request.h"
#include "target.h"
#include "snake_object.h"

void
handle_event(struct snake_type **snake,
		struct coordinates_list **tar,
		struct coordinates_list **bar,
		struct round_settings *cfg,
		struct coordinates *crd)
{
	display_in_fog_of_war((*snake)->first->coord, *tar, *bar);

	if (is_contact_with_borders((*snake)->first->coord) ||
	    is_contact_with_barrier((*snake)->first->coord, *bar)) {
		game_settings_decrease(cfg);

		if (cfg->round_num < 1) {
			if (affirmative_answer_to_continue_game_request()) {
				reset_settings(cfg);
				setup_objects(snake, tar, bar, *cfg, crd);

				/* TODO: better solution should be done: */
				return;

			} else {
				cleanup(snake, tar, bar);
				end(quit);
			}
		}

		setup_objects(snake, tar, bar, *cfg, crd);
	}

	if (is_contact_with_target((*snake)->first->coord, *tar)) {
		update_after_contact_with_target(cfg, snake, (*snake)->first->coord);

		if (cfg->current_snake_length > max_snake_length) {
			game_settings_increase(cfg);
			
			if (cfg->round_num > max_round_num) {
				end(win);
			}

			setup_objects(snake, tar, bar, *cfg, crd);
		}
	}
}

void
cleanup(struct snake_type **snake,
	struct coordinates_list **tar,
	struct coordinates_list **bar)
{
	if (*snake) {
		delete_coordinate_list(&((*snake)->first));
		(*snake)->last = NULL;
	}

	if (*tar) {
		delete_coordinate_list(tar);
	}

	if (*tar) {
		delete_coordinate_list(bar);
	}
}
